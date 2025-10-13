#include "Player.h"
#include "System/Input.h"
#include <imgui.h>
#include "Collision.h"
#include "EffectManager.h"
#include "System/Audio.h"
#include "stage.h"
#include "RayCast.h"
#include <random>
#include "BulletRotate.h"
#include "ParentChild.h"
#include "KeyInput.h"
#include "BaconBox.h"
#include "omurice.h"

#define DEBUG

Player::Player()
{
	hitEffect = new Effect("Data/Effect/Hit.efk");

	//�q�b�gSE�ǂݍ���
	hitSE = Audio::Instance().LoadAudioSource("Data/Sound/Hit.wav");

	Initialize();
}

Player::~Player()
{
	delete hitSE;

	delete hitEffect;
}

void Player::Initialize()
{
	model = std::make_unique<Model>("Data/Model/kyara.mdl");

	//���f�����傫������X�P�[�����O
	scale.x = scale.y = scale.z = 0.1f;

	HP = 10;
}

void Player::Finalize()
{
}

//�X�V����
void Player::Update(float elapsdTime, const Camera* camera, const StageManager* stage,FoodManager* foodMnager,DishManager* dishManager)
{
	InputMove(elapsdTime,camera);

	//�W�����v���͏���
	InputJump();

	//���͍X�V����
	UpdateVelocity(elapsdTime,stage->GetFloor());

	////�v���C���[�ƓG�̏Փˏ���
	//CollisionPlayerVsEnemies(enemyManager);

	
	DirectX::XMFLOAT3 childrenByeByePos = { 0,5.0f,15.0f};

	KeyInput k;

	if (k.GetKeyDown('E'))
	{
		takeItem(foodMnager,dishManager);
	}

	if (k.GetKeyDown('Q'))
	{
		DropItem(foodMnager,dishManager, stage);
	}

	if (haveIng)
	{
		ParentChild::MakeParentAndChild(transform, haveIng->getPosition(), haveIng->getScale(), haveIng->getAngle(), haveIng->getTransform(), childrenByeByePos);
		haveIng->setScale({ 1,1,1 });
	}
	if (haveDish)
	{
		ParentChild::MakeParentAndChild(transform, haveDish->getPosition(), haveDish->getScale(), haveDish->getAngle(), haveDish->getTransform(), childrenByeByePos);
		haveDish->setScale({ 0.1f,0.1f,0.1f });
	}



		
	//DirectX::XMFLOAT3 outPos;
	//if (Collision::IntersectBoxVsCylinder(stage->GetBoxPosition(0), stage->GetBoxLength(0), position, radius, height, outPos))
	//{
	//	position = outPos;
	//}
	//if (Collision::IntersectBoxVsCylinder(stage->GetBoxPosition(0), stage->GetBoxLength(0), position, radius, height, outPos))
	//{
	//	position = outPos;
	//}

	//���G���ԍX�V
	UpdateInvincidleTimer(elapsdTime);

	//�I�u�W�F�N�g�s��X�V
	UpdateTransfom();

	//���f���s��X�V
	model->UpdateTransform();

	//�G�t�F�N�g�X�V����
	EffectManager::Instance().Update(elapsdTime);
}

//�`�揈��
void Player::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);

	//�G�t�F�N�g�X�V����
	EffectManager::Instance().Render(rc.view, rc.projection);
}

//�f�o�b�O�pGUI�`��
void Player::DrawDebugGUI()
{
#ifdef DEBUG
	//�Ȃ񂩂̃|�W�V����������Ă���
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	//�\���ꏊ
	ImGui::SetNextWindowPos(ImVec2(pos.x + 10, pos.y + 10), ImGuiCond_Once);
	//�傫��
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Player", nullptr, ImGuiWindowFlags_None))
	{
		//�g�����X�t�H�[��
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//�ʒu
			ImGui::InputFloat3("Position", &position.x);

			//��]
			DirectX::XMFLOAT3 a;

			a.x = DirectX::XMConvertToDegrees(angle.x);
			a.y = DirectX::XMConvertToDegrees(angle.y);
			a.z = DirectX::XMConvertToDegrees(angle.z);
			ImGui::InputFloat3("Angle", &a.x);
			angle.x = DirectX::XMConvertToRadians(a.x);
			angle.y = DirectX::XMConvertToRadians(a.y);
			angle.z = DirectX::XMConvertToRadians(a.z);

			//�X�P�[��
		}
	}
	ImGui::End();

#endif // DEBUG
}

void Player::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{

	//���N���X�̊֐��Ăяo��
	Character::RenderDebugPrimitive(rc, renderer);

	//�e�ۃf�o�b�O�v���~�e�B�u�`��
	//projectileManager.RenderDebugPrimitive(rc, renderer);
}

void Player::OnLanding()
{
	jumpCount = 0;
}

void Player::InputMove(float elapsedTime, const Camera* camera)
{
	//�i�s�x�N�g���擾
	DirectX::XMFLOAT3 moveVec = GetMoveVec(*camera);

	//�ړ�����
	Move(elapsedTime, moveVec.x, moveVec.z, moveSpeed);

	//���񏈗�
	Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);

}

DirectX::XMFLOAT3 Player::GetMoveVec(const Camera& camera) const
{
	//���͏����擾
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax         = gamePad.GetAxisLX();
	float ay         = gamePad.GetAxisLY();

	//�J���������ƃX�e�B�b�N���͒l�Ƀ��b�g�i�s�������v�Z����
	const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
	const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

	//�ړ��x�N�g����XZ���ʂɐ����ȃx�N�g���ɂȂ�悤�ɂ���
	//�J�����E�����x�N�g����XZ�P�ʃx�N�g���ɕϊ�
	float cameraRightX      = cameraRight.x;
	float cameraRightZ      = cameraRight.z;
	float cameraRightLength = sqrtf(cameraRightX * cameraRight.x + cameraRightZ * cameraRight.z);
	if (cameraRightLength > 0.0f)
	{
		//�P�ʃx�N�g����
		cameraRightX /= cameraRightLength;
		cameraRightZ /= cameraRightLength;
	}

	//�J�����O�����x�N�g����XZ�P�ʃx�N�g���ɕϊ�
	float cameraFrontX      = cameraFront.x;
	float cameraFrontZ      = cameraFront.z;
	float cameraFrontLength = sqrtf(cameraFrontX * cameraFront.x + cameraFrontZ * cameraFront.z);
	if (cameraFrontLength > 0.0f)
	{
		//�P�ʃx�N�g����
		cameraFrontX /= cameraFrontLength;
		cameraFrontZ /= cameraFrontLength;
	}

	//�X�e�B�b�N�̐������͒l���J�����E�����ɔ��f���A
	//�X�e�B�b�N�̐������͒l���J�����O�����ɔ��f���A
	//�i�s�x�N�g�����v�Z����
	DirectX::XMFLOAT3 vec;
	vec.x = cameraRightX * ax + cameraFrontX * ay;
	vec.z = cameraRightZ * ax + cameraFrontZ * ay;

	//Y�������ɂ͈ړ����Ȃ�
	vec.y = 0.0f;

	return vec;
}

//������ǂ��A�[�g
//�v���C���[�ƃG�l�~�[�̏Փˏ���
void Player::CollisionPlayerVsEnemies(EnemyManager* enemyManager)
{
	////EnemyManager& enemyManager = EnemyManager::Instance();
	////���ׂĂ̓G�Ƒ�������ŏՓˏ���
	//int enemyConst = enemyManager->GetEnemyCount();

	//for (int i = 0; i < enemyConst; i++)
	//{
	//	Enemy* enemy = enemyManager->GetEnemy(i);

	//	//�Փˏ���
	//	DirectX::XMFLOAT3 outPositon;
	//	if (Collision::IntersectCylinderVsCylinder(
	//		position, radius, height,
	//		enemy->GetPosition(), enemy->GetRadius(), enemy->GetHeight(),
	//		outPositon))
	//	{
	//		//if (enemy->GetPosition().y + enemy->GetHeight() - position.y < 0.1)
	//		if (position.y > enemy->GetPosition().y + enemy->GetHeight() - 0.1)
	//		{
	//			jumpCount = 1;
	//			//position.y = enemy->GetPosition().y + enemy->GetHeight();
	//			Jump(jumpSpeed * 0.5f);
	//			break;
	//		}
	//		enemy->SetPosition(outPositon);
	//	}
	//}
}

void Player::InputJump()
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	if (gamePad.GetButtonDown() & GamePad::BTN_A)
	{
		if (jumpCount < jumpLimit)
		{
			jumpCount++;
			Jump(jumpSpeed);
		}
	}
}


void Player::InputProjectile(EnemyManager* enemyManager)
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	{
		//if (gamePad.GetButtonDown() & GamePad::BTN_Y)
		//{
		//	//����
		//	BulletRotate* pr = new BulletRotate(&projectileManager);
		//	pr->Launch({position.x,position.y + height * 0.5f,position.z }, pos, offset);
		//}

		//if (gamePad.GetButtonDown() & GamePad::BTN_X)
		//{
		//	std::random_device rd;
		//	std::mt19937 mt(rd());
		//	std::uniform_int_distribution<> distXZ(-3.0f,3.0f);
		//	std::uniform_int_distribution<> distY(0.5f,3.0f);
		//	//�O����
		//	DirectX::XMFLOAT3 dir;
		//	dir.x = sinf(angle.y);
		//	dir.y = 0;
		//	dir.z = cosf(angle.y);
		//	//���ˈʒu(��������)
		//	DirectX::XMFLOAT3 pos;
		//	pos.x = position.x + distXZ(mt);
		//	pos.y = position.y + height * 0.5f + distY(mt);
		//	pos.z = position.z + distXZ(mt);
		//	//�^�[�Q�b�g
		//	DirectX::XMFLOAT3 target;
		//	target.x = sinf(angle.y);
		//	target.y = 0;
		//	target.z = cosf(angle.y);
		//	//��ԋ߂��̓G���^�[�Q�b�g�ɂ���
		//	float dist = FLT_MAX;
		//	//EnemyManager& enemyManager = EnemyManager::Instance();
		//	int enemyCount = enemyManager->GetEnemyCount();
		//	for (int i = 0; i < enemyCount; i++)
		//	{
		//		//XZ���ʂł͈̔̓`�F�b�N
		//		float vx = enemyManager->GetEnemy(i)->GetPosition().x - position.x;
		//		float vy = enemyManager->GetEnemy(i)->GetPosition().y - position.y;
		//		float vz = enemyManager->GetEnemy(i)->GetPosition().z - position.z;
		//		float range = sqrtf(vx * vx + vy * vy + vz * vz);
		//		if (range < dist)
		//		{
		//			dist = range;
		//			target.x = enemyManager->GetEnemy(i)->GetPosition().x;
		//			target.y = enemyManager->GetEnemy(i)->GetPosition().y + enemyManager->GetEnemy(i)->GetHeight() * 0.5f;
		//			target.z = enemyManager->GetEnemy(i)->GetPosition().z;
		//		}
		//	}
		//	//����
		//	ProjectileHoming* pr = new ProjectileHoming(&projectileManager);
		//	pr->Launch(dir, pos, target);
		//	//projectileManager.Register(pr);
		//}
	}
}

void Player::UpdateHorizontalMove(float elapsedTime, const Stage* stage)
{
	using namespace DirectX;

	XMFLOAT3 s = {
		position.x,
		position.y + height * 0.5f,
		position.z,
	};
	XMFLOAT3 e = {
		position.x + velocity.x * elapsedTime,
		position.y + height * 0.3f,
		position.z + velocity.z * elapsedTime,
	};

	if (velocity.x > 0.001f)
	{
		int a = 0;
	}

	XMFLOAT3 p, n;

	//if (Hit::RayCast(s, e, stage->GetTransform(), &stage->GetModel(), p, n))
	//{
	//	//��_����I�_�ւ̃x�N�g�������߂�
	//	DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&p);
	//	DirectX::XMVECTOR E = DirectX::XMLoadFloat3(&e);
	//	DirectX::XMVECTOR PE = DirectX::XMVectorSubtract(E, P);

	//	//�O�p�֐��ŏI�_����ǂ܂ł̒��������߂�
	//	DirectX::XMVECTOR N = DirectX::XMLoadFloat3(&n);
	//	DirectX::XMVECTOR A = DirectX::XMVector3Dot(-PE, N);
	//	//�ǂ܂ł̒������������������Ȃ�悤�ɕ␳����
	//	float a = fabsf(DirectX::XMVectorGetX(A)) + 0.001f;

	//	//�ǂ���x�N�g�������߂�
	//	DirectX::XMVECTOR R = DirectX::XMVectorAdd(PE, DirectX::XMVectorScale(N, a));

	//	//�ǂ��肠�Ƃ̈ʒu�����߂�
	//	DirectX::XMVECTOR Q = DirectX::XMVectorAdd(P, R);
	//	DirectX::XMFLOAT3 q;
	//	DirectX::XMStoreFloat3(&q, Q);

	//	//�Ǎۂŕǂ����̈ʒu���߂荞��ł��Ȃ�����L���X�g�Ń`�F�b�N����
	//	if (Hit::RayCast(s, q, stage->GetTransform(), &stage->GetModel(), p, n))
	//	{
	//		//�߂荞��ł����ꍇ�̓v���C���[�̈ʒu�ɍ���̗�L���X�g������_��ݒ肷��
	//		//�v���C���[�̈ʒu���ǂɂ҂����肭�����Ȃ��悤�ɕ␳����
	//		P = DirectX::XMLoadFloat3(&p);
	//		DirectX::XMVECTOR S = DirectX::XMLoadFloat3(&s);
	//		DirectX::XMVECTOR PS = DirectX::XMVectorSubtract(S, P);
	//		DirectX::XMVECTOR V = XMVector3Normalize(PS);
	//		P = XMVectorAdd(P, XMVectorScale(V, 0.001f));
	//		DirectX::XMStoreFloat3(&p, P);
	//		position.x = p.x;
	//		position.z = p.z;
	//	}
	//	else
	//	{
	//		position.x = q.x;
	//		position.z = q.z;
	//	}

	//}
	{
		Character::UpdateHorizontalMove(elapsedTime, stage);
	}
}

void Player::UpdateVerticalMove(float elapsedTime, const Stage* stage)
{
	float MoveY = velocity.y * elapsedTime;

	bool IsGround = isGround;
	isGround = IsGround;

	//�������ɐݒu����������
	if (velocity.y < 0.0f)
	{

		DirectX::XMFLOAT3 S = { position.x, position.y + height * 0.5f, position.z };
		DirectX::XMFLOAT3 E = { position.x, position.y + gravity * elapsedTime , position.z };

		float DownHillOffset = downhillOffset * elapsedTime;

		if (IsGround)
		{
			E.y -= DownHillOffset;
			isGround = false;
		}
		DirectX::XMFLOAT3 hitPos, hitNormal;
		if (Hit::RayCast(S, E, stage->GetTransform(), &stage->GetModel(), hitPos, hitNormal))
		{
			//��_��Y���W���v���C���[�̈ʒu�ɂ���
			position.y = hitPos.y;
			velocity.y = 0.0f;
			MoveY = velocity.y * elapsedTime;
			isGround = true;
			OnLanding();
		}
	}

	position.y += MoveY;

	position.y = 0.0f;

}

void Player::Cocking(float elapsedTime, const StageManager* stageManager)
{
	//���ׂẴ}�b�v�`�b�v�𔻒肵�Ĉ�ԋ߂������ł�����̂𒲂ׂ�
	//for (int i = 0;i < stageManager.GetTileMapLength();i++)
	//{
	//	stageManager
	//}
}

bool Player::ApplyDamage(float dmage, float invincidleTime)
{
	//�_���[�W��0�̏ꍇ�͌��N��Ԃ�ύX����K�v���Ȃ�
	if (dmage == 0) return false;

	//���S���Ă���ꍇ�͌��N��Ԃ�ύX���Ȃ�
	if (HP <= 0) return false;

	if (invincidleTimer > 0) return false;

	invincidleTimer = invincidleTime;

	//�_���[�W����
	HP -= dmage;

	//���N��Ԃ�ύX�����ꍇ��true��Ԃ�
	return true;
}

void Player::takeItem(FoodManager* foodmanager,DishManager* dishManager)
{
	float nearItem;
	//float nearBox;
	float nearDish;
	{
		//��ԋ߂��M�����𔻕ʂ��Ď�Ɏ���
		DirectX::XMFLOAT3 itemPos;
		DirectX::XMFLOAT3 dishPos;
		Ingredients* nearestItem = nullptr;
		Dish* nearestDish = nullptr;
		float ingDis = FLT_MAX;
		float dishDis = FLT_MAX;
		for (int i = 0; i < foodmanager->GetFoodCount(); i++)
		{
			Ingredients* item = foodmanager->GetFood(i);
			if (item == haveIng)
			{
				continue;
			}

			itemPos = item->getPosition();

			float vx = itemPos.x - position.x;
			float vz = itemPos.z - position.z;
			float Length = sqrtf(vx * vx + vz * vz);

			float distance = radius + foodmanager->GetFood(i)->getRadius();

			if (distance > Length&&Length <ingDis)
			{
				ingDis = Length;
				nearestItem = item;
			}
		}
		for (int j = 0; j < dishManager->getDishNum();j++)
		{
		
			Dish* dish = dishManager->getDish(j);
			dishPos = dish->getPosition();

			if (dish == haveDish)
			{
				continue;
			}


			float vx = dishPos.x - position.x;
			float vz = dishPos.z - position.z;
			float Length = sqrtf(vx * vx + vz * vz);

			float distance = radius + dishManager->getDish(j)->getRadius();

			if (distance > Length && Length < dishDis)
			{
				dishDis = Length;
				nearestDish = dish;
			}
		}

		if (haveIng != nullptr && haveDish != nullptr)
		{
			haveDish->setOndishFood(nearestItem);
			haveIng = haveDish->MixDishOnFood(haveIng, foodmanager);
			return;
		}
		
		if (nearestDish != nullptr && (dishDis <= ingDis || nearestItem == nullptr))
		{
			haveDish = nearestDish;
		}
		else if (nearestItem != nullptr)
		{
			haveIng = nearestItem;
		}

	}
}

void Player::DropItem(const FoodManager* foodManager,const DishManager* dishManager,const StageManager* stagemanager)
{

	DirectX::XMFLOAT3 dropPos = position;
	dropPos.y = 0;
	//�v���C���[�̑����ɒu��
	if (haveIng)
	{
		haveIng->setPosition(dropPos);
		haveIng->setScale({ 0.1f,0.1f,0.1f });

		haveIng->UpdateTransfom();
		haveIng = nullptr;
	}

	if (haveDish)
	{
		

		haveDish->setPosition(dropPos);
		haveDish->setScale({ 0.01f,0.01f,0.01f });

		haveDish->UpdateTransfom();
		//haveIng->model->UpdateTransform();

		haveDish = nullptr;
	}
}

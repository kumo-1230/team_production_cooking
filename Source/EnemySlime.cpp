#include "EnemySlime.h"
#include "mathUtils.h"
#include "Player.h"
#include "EnemyManager.h"
#include <random>
#include "Collision.h"


EnemySlime::EnemySlime()
{
	model.reset(new Model("Data/Model/Slime/Slime.mdl"));
	em.reset(new EnemyManager());
	//�X�P�[�����O
	scale.x = scale.y = scale.z = 0.01f;

	weaponManager.reset(new WeaponManager());

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> mode(0,3);
	std::uniform_int_distribution<> Lv(0,3);

	weaponManager->SetWeaponBild(mode(rd), Lv(rd));

	weaponManager->SetWeapon();

	//�������ݒ�
	radius = 0.5f;
	height = 1.0f;
	hitEffect.reset(new Effect("Data/Effect/Hit.efk"));

	//�q�b�gSE�ǂݍ���
	hitSE.reset(Audio::Instance().LoadAudioSource("Data/Sound/Hit.wav"));

}

EnemySlime::~EnemySlime()
{
}

void EnemySlime::Update(float elapsedTime,Player* player, const Stage* stage,EnemyManager* enemyManager)
{
	lifeTimer = 1;
	lifeTimer -= 1 * elapsedTime;

	targetPositon = player->GetPosition();

	MoveToTarget(elapsedTime, 1.0f, 1.0f);

	//���͏����X�V
	UpdateVelocity(elapsedTime,stage);

	DirectX::XMFLOAT3 outPosition;
	if (Collision::IntersectCylinderVsCylinder(
		position, radius, height,
		player->GetPosition(), player->GetRadius(), player->GetHeight(),
		outPosition))
	{
		if (player->ApplyDamage(1.0f, 0.5f))
		{
			HitImpact(position, player->GetPosition(), 5.0f, player);
			Destroy(enemyManager);
		}
	}

	//�e�ۍX�V����
	weaponManager->Update(elapsedTime, *player, *em.get(), *this, LCHAR::ENEMY);

	//���G���ԍX�V
	UpdateInvincidleTimer(elapsedTime);

	//�I�u�W�F�N�g�s��X�V
	UpdateTransfom();

	//���f���s��X�V
	model->UpdateTransform();
}

void EnemySlime::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);
	//�e�ە`��
	//projectileManager.Render(rc, renderer);
	weaponManager->Render(rc, renderer);
}

void EnemySlime::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	//���N���X�̃f�o�b�O�v���~�e�B�u�`��
	Enemy::RenderDebugPrimitive(rc, renderer);
	//�^�[�Q�b�g�ʒu���f�o�b�O
	renderer->RenderSphere(rc, targetPositon, 1.0f, DirectX::XMFLOAT4(1, 1, 0, 1));
	//�{���͈͂��f�o�b�O�~���`��
	renderer->RenderCylinder(rc, position, searchRange, 1.0f, DirectX::XMFLOAT4(1, 0, 0, 1));
}

//���S�������ɌĂ΂��
void EnemySlime::OnDead(EnemyManager* enemyManager)
{
	//���g���폜
	//delete this;
	Destroy(enemyManager);
}

//�ړI�n�ֈړ�
void EnemySlime::MoveToTarget(float elapsedTime, float moveSpeedRate, float turnSpeedRate)
{
	//�^�[�Q�b�g�����ւ̐i�s�x�N�g�����Z�o
	float vx = targetPositon.x - position.x;
	float vz = targetPositon.z - position.z;
	float dist = sqrtf(vx * vx + vz * vz);
	//���K��
	vx /= dist;
	vz /= dist;

	//�ړ�����
	Move(elapsedTime, vx, vz, moveSpeed * moveSpeedRate);
	Turn(elapsedTime, vx, vz, turnSpeed * turnSpeedRate);
}

//���������G�l�~�[�ƒe�̓����蔻��
void EnemySlime::CollisionPlayerVsBullet(Player* p)
{
	//���ׂĂ̒e�ۂƂ��ׂẴv���C���[�𑍓�����ŏՓˏ���
	int weaponCount = weaponManager->GetWeaponCount();
	for (int i = 0; i < weaponCount; i++)
	{
		Weapon* weapon = weaponManager->GetWeaponIndex(i);
		if (weapon->GetInvisibule() == false)
		{
			//�Փˏ���
			DirectX::XMFLOAT3 outPosition;
			if (Collision::IntersectSphereVsCylinder(
				weapon->GetPosition(),
				weapon->GetRadius(),
				p->GetPosition(),
				p->GetRadius(),
				p->GetHeight(),
				outPosition))
			{
				//�_���[�W��^����
				if (p->ApplyDamage(weapon->GetAttackPower(), 0.5f))
				{
					HitImpact(weapon->GetPosition(), p->GetPosition(), 5.0f, p);
					//�e�۔j��
					weapon->Destroy();
				}
			}
		}
	}
}

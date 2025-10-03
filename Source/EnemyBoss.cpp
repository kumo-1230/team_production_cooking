#include "EnemyBoss.h"
#include "mathUtils.h"
#include "Player.h"
#include "EnemyManager.h"
#include "EnemySlime.h"
#include "Collision.h"
#include "Enemy.h"
#include <random>


EnemyBoss::EnemyBoss()
{
	model.reset(new Model("Data/Model/Slime/Slime.mdl"));
	em.reset(new EnemyManager());
	//�X�P�[�����O
	scale.x = scale.y = scale.z = 0.01f;

	weaponManager.reset(new WeaponManager());

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> Lv(3, 5);

	for (int i = 0; i < 3; i++)
	{
		weaponManager->SetWeaponBild(i, Lv(rd));
	}

	weaponManager->SetWeapon();

	//�������ݒ�
	radius = 0.5f;
	height = 1.0f;

	hitEffect.reset(new Effect("Data/Effect/Hit.efk"));

	//�q�b�gSE�ǂݍ���
	hitSE.reset(Audio::Instance().LoadAudioSource("Data/Sound/Hit.wav"));

	//�p�j�X�e�[�g�֑J��
	SetEanderState();
}

EnemyBoss::~EnemyBoss()
{
	em->Clear();
}

void EnemyBoss::Update(float elapsedTime, Player* player, const Stage& stage, EnemyManager* enemyManager)
{
	//�X�e�[�g�}�C�̍X�V����
	switch (state)
	{
	case State::Wander:
		UpdatWanderState(elapsedTime, player);
		break;
	case State::Idle:
		UpdatetIdleState(elapsedTime, player);
		break;
	case State::Attack:
		UpdateAttackState(elapsedTime, player);
		break;
	case State::SummonEnemy:
		UpdateSummonEnemyState(elapsedTime, player);
		break;
	case State::Warp:
		UpdateWarpState(elapsedTime, player);
		break;
	}

	//���͏����X�V
	UpdateVelocity(elapsedTime, stage);

	//�e�ۍX�V����
	weaponManager->Update(elapsedTime, *player, *em.get(), *this, LCHAR::ENEMY);

	//�v���C���[�Ƌ��̏Փˏ���
	CollisionPlayerVsBullet(player);

	//���G���ԍX�V
	UpdateInvincidleTimer(elapsedTime);

	//�I�u�W�F�N�g�s��X�V
	UpdateTransfom();

	em->Update(elapsedTime,player,stage);

	//���f���s��X�V
	model->UpdateTransform();
}

void EnemyBoss::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);
	//�e�ە`��
	//projectileManager.Render(rc, renderer);
	weaponManager->Render(rc, renderer);

	em->Render(rc, renderer);
}

//�f�o�b�O
void EnemyBoss::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	//���N���X�̃f�o�b�O�v���~�e�B�u�`��
	Enemy::RenderDebugPrimitive(rc, renderer);
	//�꒣��̃f�o�b�O
	renderer->RenderCylinder(rc, territoryOrigin, moveTerritory, 1.0f, DirectX::XMFLOAT4(0, 1, 0, 1));
	//�꒣��̃f�o�b�O
	renderer->RenderCylinder(rc, territoryOrigin, summonTerritory, 1.0f, DirectX::XMFLOAT4(1, 0, 0, 1));
	//�꒣��̃f�o�b�O
	renderer->RenderCylinder(rc, territoryOrigin, warpTerritory, 1.0f, DirectX::XMFLOAT4(0, 0, 1, 1));
	//�^�[�Q�b�g�ʒu���f�o�b�O
	renderer->RenderSphere(rc, targetPositon, 1.0f, DirectX::XMFLOAT4(1, 1, 0, 1));
	//�{���͈͂��f�o�b�O�~���`��
	//renderer->RenderCylinder(rc, position, searchRange, 1.0f, DirectX::XMFLOAT4(1, 0, 0, 1));
}



//�p�j�X�e�[�g�֑J��
void EnemyBoss::SetEanderState()
{
	state = State::Wander;

	//�ړI�n�_�ݒ�
	SetRandomTargetPosition(0.0f, moveTerritory);
}

//�ҋ@�X�e�[�g�֑J��
void EnemyBoss::SetIdleaState()
{
	state = State::Idle;

	//�^�C�}�[�������_���ݒ�
	stateTimer = MathUtils::RandomRange(1.0f, 2.0f);
}

void EnemyBoss::SetAttackState(Player* player)
{
	state = State::Attack;
	stateTimer = 0.0f;
	//�����_���Ȋp�x
	float theta = MathUtils::RandomRange(-DirectX::XM_PI, DirectX::XM_PI);
	//�����_���ȏꏊ
	float range = MathUtils::RandomRange(3.0f, moveTerritory);
	//�I���W������^�[�Q�b�g�܂ł��v�Z���ăZ�b�g����
	targetPositon.x = player->GetPosition().x + sinf(theta) * range;
	targetPositon.y = player->GetPosition().y;
	targetPositon.z = player->GetPosition().z + cosf(theta) * range;
}

void EnemyBoss::SetSummonEnemy(Player* player)
{
	state = State::SummonEnemy;
	stateTimer = 3.0f;
	if (em->GetEnemyCount() < 4)
	{
		for (int i = 0; i < 2; i++)
		{
			SetRandomTargetPosition(0.0f, summonTerritory);
			SummonPos[i] = targetPositon;
		}
	}
	//�����_���Ȋp�x
	float theta = MathUtils::RandomRange(-DirectX::XM_PI, DirectX::XM_PI);
	//�����_���ȏꏊ
	float range = MathUtils::RandomRange(3.0f, moveTerritory);
	//�I���W������^�[�Q�b�g�܂ł��v�Z���ăZ�b�g����
	targetPositon.x = player->GetPosition().x + sinf(theta) * range;
	targetPositon.y = player->GetPosition().y;
	targetPositon.z = player->GetPosition().z + cosf(theta) * range;
}

void EnemyBoss::SetWarpState()
{
	state = State::Warp;

	//���[�v�܂ł̃^�C�}�[��ݒ�
	stateTimer = 1.0f;
}

//�꒣��ݒ�
void EnemyBoss::SetTerritory(const DirectX::XMFLOAT3& origin, float range)
{
	territoryOrigin = origin;
}

void EnemyBoss::SetRandomTargetPosition(float start, float end)
{
	//�����_���Ȋp�x
	float theta = MathUtils::RandomRange(-DirectX::XM_PI, DirectX::XM_PI);
	//�����_���ȏꏊ
	float range = MathUtils::RandomRange(start, end);
	//�I���W������^�[�Q�b�g�܂ł��v�Z���ăZ�b�g����
	targetPositon.x = territoryOrigin.x + sinf(theta) * range;
	targetPositon.y = territoryOrigin.y;
	targetPositon.z = territoryOrigin.z + cosf(theta) * range;
}



//�v���C���[���O�ɂ��邩
bool EnemyBoss::SearchPlayer(Player* player)
{
	//�v���C���[�Ƃ̍m�肳���l������3D�ł̋������������
	const DirectX::XMFLOAT3& playerPosition = player->GetPosition();
	float vx = playerPosition.x - position.x;
	float vy = playerPosition.y - position.y;
	float vz = playerPosition.z - position.z;
	float dist = sqrtf(vx * vx + vy * vy + vz * vz);
	if (dist < moveTerritory)
	{
		float distXZ = sqrtf(vx * vx + vz * vz);
		//�P�ʃx�N�g����
		vx /= distXZ;
		vz /= distXZ;
		//�O���x�N�g��
		float frontX = sinf(angle.y);
		float frontZ = cosf(angle.y);
		//��̃x�N�g���̂Ȃ��Ȓl�őO�㔻��
		float dot = (frontX * vx) + (frontZ * vz);
		if (dot > 0.0f)
		{
			return true;
		}
	}
	return false;
}

bool EnemyBoss::SearchPlayerZone(Player* player, float start, float end)
{
	//�v���C���[�Ƃ̍m�肳���l������3D�ł̋������������
	const DirectX::XMFLOAT3& playerPosition = player->GetPosition();
	float vx = playerPosition.x - position.x;
	float vy = playerPosition.y - position.y;
	float vz = playerPosition.z - position.z;
	float dist = sqrtf(vx * vx + vy * vy + vz * vz);
	if (dist > start && dist < end)
	{
		return true;
	}
	return false;
}

//�ړI�n�ֈړ�
void EnemyBoss::MoveToTarget(float elapsedTime, float moveSpeedRate, float turnSpeedRate, const DirectX::XMFLOAT3& Pos)
{
	//�^�[�Q�b�g�����ւ̐i�s�x�N�g�����Z�o
	float vx = Pos.x - position.x;
	float vz = Pos.z - position.z;
	float dist = sqrtf(vx * vx + vz * vz);
	//���K��
	vx /= dist;
	vz /= dist;
	//�ړ�����
	Move(elapsedTime, vx, vz, moveSpeed * moveSpeedRate);
	Turn(elapsedTime, vx, vz, turnSpeed * turnSpeedRate);
}

//���������G�l�~�[�ƒe�̓����蔻��
void EnemyBoss::CollisionSummonEnemyVsBullet(Weapon* w, Effect* hitEffect, AudioSource* hitSE)
{
	for (int i = 0; i < em->GetEnemyCount(); i++)
	{
		Enemy* e = em->GetEnemy(i);
		//�Փˏ���
		DirectX::XMFLOAT3 outPosition;
		if (Collision::IntersectSphereVsCylinder(
			w->GetPosition(),
			w->GetRadius(),
			e->GetPosition(),
			e->GetRadius(),
			e->GetHeight(),
			outPosition))
		{
			//�_���[�W��^����
			if (e->ApplyDamage(w->GetAttackPower(), 0.5f, em.get()))
			{
				HitImpact(w->GetPosition(), e->GetPosition(), 5.0f, e);
				//�e�۔j��
				w->Destroy();
			}
		}
	}
}

//�����e�ƃv���C���[�̓����蔻��
void EnemyBoss::CollisionPlayerVsBullet(Player* p)
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

//�p�j�X�e�[�g�X�V����
void EnemyBoss::UpdatWanderState(float elapsedTime, Player* player)
{
	//�ړI�n�܂�XZ���ʂł̈ړ�����
	float vx = targetPositon.x - position.x;
	float vz = targetPositon.z - position.z;
	float distSq = vx * vx + vz * vz;
	if (distSq < radius * radius)
	{
		//���̖ړI�n�_�ݒ�
		territoryOrigin = position;
		SetIdleaState();
	}

	//�ړI�n�_�ֈړ�
	MoveToTarget(elapsedTime, 1.0f, 1.0f,targetPositon);

	//�v���C���[�{��
	if (SearchPlayer(player))
	{
		//��������U���X�e�[�g��
		SetAttackState(player);
	}
	//���[�v�]�[���Ƀv���C���[�����邩
	if (SearchPlayerZone(player,summonTerritory,warpTerritory))
	{
		//�������烏�[�v
		SetWarpState();
	}
	//�����]�[���ɂ��邩
	if (SearchPlayerZone(player, moveTerritory, summonTerritory))
	{
		SetSummonEnemy(player);
	}
}

//�ҋ@�X�e�[�g�X�V
void EnemyBoss::UpdatetIdleState(float elaspedTime, Player* player)
{
	//�^�C�}�[����
	stateTimer -= elaspedTime;
	if (stateTimer < 0.0f)
	{
		//�p�j�X�e�[�g�֑J��
		SetEanderState();
	}

	//�v���C���[�{��
	if (SearchPlayer(player))
	{
		//��������U���X�e�[�g��
		SetAttackState(player);
	}
}

//�ǐՃX�e�[�g�X�V����
void EnemyBoss::UpdateAttackState(float elapsedTime, Player* player)
{
	//�ړI�n�܂�XZ���ʂł̈ړ�����
	float vx = targetPositon.x - position.x;
	float vz = targetPositon.z - position.z;
	float distSq = vx * vx + vz * vz;
	if (distSq < radius * radius)
	{
		SetRandomTargetPosition(0.0f, moveTerritory);
		stateTimer = 0.5f;
	}

	//�ړI�n�ֈړ�
	MoveToTarget(elapsedTime, 0.0f, 1.0f,player->GetPosition());
	MoveToTarget(elapsedTime, 1.0f, 0.0f,targetPositon);

	//���[�v�]�[���Ƀv���C���[�����邩
	if (SearchPlayerZone(player, summonTerritory, warpTerritory))
	{
		//�������烏�[�v
		SetWarpState();
	}
	//�����]�[���ɂ��邩
	if (SearchPlayerZone(player, moveTerritory, summonTerritory))
	{
		SetSummonEnemy(player);
	}

	//�^�C�}�[����
	stateTimer -= elapsedTime;
	if (stateTimer < 0.0f)
	{
		//�O����
		DirectX::XMFLOAT3 dir;
		dir.x = sinf(angle.y);
		dir.y = 0.0f;
		dir.z = cosf(angle.y);
		//���ˈʒu
		DirectX::XMFLOAT3 pos;
		pos.x = position.x;
		pos.y = position.y + height * 0.5f;
		pos.z = position.z;
		//����
		weaponManager->GetWeapon(WEAPON::BULLET_STRAIGHT)->SetCoolTime();
		stateTimer = 2.0f;

		if (!SearchPlayer(player))
		{
			//�ҋ@�X�e�[�g�֑J��
			SetIdleaState();
		}
	}
}

void EnemyBoss::UpdateSummonEnemyState(float elapsedTime, Player* player)
{
	stateTimer -= 1 * elapsedTime;

	//�ړI�n�_�ֈړ�
	MoveToTarget(elapsedTime, 1.0f, 1.0f,targetPositon);
	//�ړI�n�܂�XZ���ʂł̈ړ�����
	float vx = targetPositon.x - position.x;
	float vz = targetPositon.z - position.z;
	float distSq = vx * vx + vz * vz;
	if (distSq < radius * radius)
	{
		stateTimer = 0.0f;
	}
	if (Collision::IntersectSphereVsCylinder(
		targetPositon, 1.0f,
		position, radius, height))
	{
		//���̖ړI�n�_�ݒ�
		territoryOrigin = position;
	}
	territoryOrigin = position;
	if (stateTimer <= 0.0f)
	{
		EnemySlime* enemy;
		for (int i = 0; i < 2; i++)
		{
			if (em->GetEnemyCount() < 4)
			{
				enemy = new EnemySlime();
				enemy->SetPosition({ SummonPos[i].x,0,SummonPos[i].y });
				em->Register(enemy);
			}
		}
		SetEanderState();
	}
}

void EnemyBoss::UpdateWarpState(float elapsedTime, Player* player)
{
	stateTimer -= 1 * elapsedTime;

	if (stateTimer < 0.0f)
	{
		//���[�v�]�[���͈͂Ƀ����_���Ƀ��[�v
		//�����_���Ȋp�x
		float theta = MathUtils::RandomRange(-DirectX::XM_PI, DirectX::XM_PI);
		//�����_���ȏꏊ
		float range = MathUtils::RandomRange(3.0f, moveTerritory);
		//�I���W������^�[�Q�b�g�܂ł��v�Z���ăZ�b�g����
		targetPositon.x = player->GetPosition().x + sinf(theta) * range;
		targetPositon.y = player->GetPosition().y;
		targetPositon.z = player->GetPosition().z + cosf(theta) * range;
		//���[�v
		position = targetPositon;

		territoryOrigin = position;
		SetEanderState();

	}

	if (!SearchPlayerZone(player, summonTerritory, warpTerritory))
	{
		SetEanderState();
	}
}

//���S�������ɌĂ΂��
void EnemyBoss::OnDead(EnemyManager* enemyManager)
{
	//���g���폜
	//delete this;
	Destroy(enemyManager);
}

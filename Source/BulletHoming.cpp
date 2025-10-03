#include "BulletHoming.h"
#include <random>
#include "Player.h"
#include "EnemyManager.h"
#include "Enemy.h"

BulletHoming::BulletHoming(int Lv) : Weapon(WEAPON::BULLET_HOMING)
{
	model.reset(new Model("Data/Model/Sword/Sword.mdl"));

	//�X�P�[�����O
	scale.x = scale.y = scale.z = 3.0f;
	switch (Lv)
	{
	case 1:
		InitializeLv1();
		break;
	case 2:
		InitializeLv2();
		break;
	case 3:
		InitializeLv3();
		break;
	case 4:
		InitializeLv4();
		break;
	case 5:
		InitializeLv5();
		break;
	}
	coolTimeBank = coolTime;
	lifeTimerBank = lifeTimer;
}

BulletHoming::~BulletHoming()
{
}

void BulletHoming::InitializeLv1()
{
	moveSpeed = 10.0f;
	lifeTimer = 2.0f;
	coolTime = 1.0f;
}

void BulletHoming::InitializeLv2()
{
	moveSpeed = 15.0f;
	lifeTimer = 3.0f;
	coolTime = 0.8f;
}

void BulletHoming::InitializeLv3()
{
	moveSpeed = 20.0f;
	lifeTimer = 3.0f;
	coolTime = 0.6f;
}

void BulletHoming::InitializeLv4()
{
	moveSpeed = 25.0f;
	lifeTimer = 3.0f;
	coolTime = 0.4f;
}

void BulletHoming::InitializeLv5()
{
	moveSpeed = 30.0f;
	lifeTimer = 3.0f;
	coolTime = 0.2f;
}

void BulletHoming::Update(float elapsedTime)
{
	//�����X�V
	lifeTimer -= 1 * elapsedTime;
	if (lifeTimer < 0)
	{
		//�����폜
		Destroy();
	}

	//�ړ�
	float speed = this->moveSpeed * elapsedTime;
	position.x += direction.x * speed;
	position.y += direction.y * speed;
	position.z += direction.z * speed;

	//����
	float turnS = this->turnSpeed * elapsedTime;

	//�^�[�Q�b�g�܂ł̃x�N�g�����Z�o
	DirectX::XMVECTOR Position = DirectX::XMLoadFloat3(&position);
	DirectX::XMVECTOR Target = DirectX::XMLoadFloat3(&target);
	DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Target, Position);

	//�[���x�N�g���łȂ��Ȃ��]����
	DirectX::XMVECTOR Lengthsq = DirectX::XMVector3Length(Vec);
	float lengthSq;
	DirectX::XMStoreFloat(&lengthSq, Lengthsq);
	if (lengthSq > 0.00001f)
	{
		//�^�[�Q�b�g�܂ł̃x�N�g����P�ʃx�N�g����
		Vec = DirectX::XMVector3Normalize(Vec);

		//�����Ă�����x�N�g�����Z�o
		DirectX::XMVECTOR Direction = DirectX::XMLoadFloat3(&direction);

		//�O�����x�N�g���ƃ^�[�Q�b�g�܂ł̓��ς��Z�o
		DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(Direction, Vec);

		float dot;
		//DirectX::XMStoreFloat(&dot, Dot);
		dot = DirectX::XMVectorGetX(Dot);

		//�Ȃ��Ȓl��-1.0�`1.0�ŕ\������Ă���A��̒P�ʃx�N�g���̊p�x��
		//�������ق�1.0�ɋ߂Â��Ƃ��������𗘗p���ĉ�]���x�𒲐߂���
		float rot = acosf(dot);
		if (rot > turnS) rot = turnS;

		//��]�p�x������Ȃ��]����������
		if (fabsf(rot) > 0.0001f)
		{
			//��]�����Z�o(�O��)
			DirectX::XMVECTOR Axis = DirectX::XMVector3Cross(Direction, Vec);
			Axis = DirectX::XMVector3Normalize(Axis);

			//��]���Ɖ�]�ʂ����]�s����Z�o(�N�H�[�^�j�I��)
			DirectX::XMVECTOR Rotation = DirectX::XMQuaternionRotationAxis(Axis, rot);

			//���݂̑O��������]������
			Direction = DirectX::XMVector3Rotate(Direction, Rotation);

			//�ϊ�
			DirectX::XMStoreFloat3(&direction, Direction);
		}
	}
	//�I�u�W�F�N�g�s����X�V
	UpdateTransform();

	//���f���s��X�V
	model->UpdateTransform();
}

void BulletHoming::Launch(const Player& p, const EnemyManager& em, const Enemy& e, int lanchChar)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> distXZ(-3.0f, 3.0f);
	std::uniform_int_distribution<> distY(0.5f, 3.0f);

	if (lanchChar == LCHAR::PLAYER)
	{
		//�O����
		DirectX::XMFLOAT3 dir;
		direction.x = sinf(p.GetAngle().y);
		direction.y = 0;
		direction.z = cosf(p.GetAngle().y);
		//���ˈʒu(��������)
		DirectX::XMFLOAT3 pos;
		position.x = p.GetPosition().x + distXZ(mt);
		position.y = p.GetPosition().y + p.GetHeight() * 0.5f + distY(mt);
		position.z = p.GetPosition().z + distXZ(mt);
		//�^�[�Q�b�g
		target.x = sinf(p.GetAngle().y);
		target.y = 0;
		target.z = cosf(p.GetAngle().y);
		//��ԋ߂��̓G���^�[�Q�b�g�ɂ���
		float dist = FLT_MAX;
		int enemyCount = em.GetEnemyCount();
		for (int i = 0; i < enemyCount; i++)
		{
			//XZ���ʂł͈̔̓`�F�b�N
			float vx = em.GetEnemyPos(i).x - position.x;
			float vy = em.GetEnemyPos(i).y - position.y;
			float vz = em.GetEnemyPos(i).z - position.z;
			float range = sqrtf(vx * vx + vy * vy + vz * vz);
			if (range < dist)
			{
				dist = range;
				target.x = em.GetEnemyPos(i).x;
				target.y = em.GetEnemyPos(i).y + em.GetEnemyHeight(i) * 0.5f;
				target.z = em.GetEnemyPos(i).z;
			}
		}
	}
	else if (lanchChar == LCHAR::ENEMY)
	{
		//�O����
		DirectX::XMFLOAT3 dir;
		direction.x = sinf(e.GetAngle().y);
		direction.y = 0;
		direction.z = cosf(e.GetAngle().y);
		//���ˈʒu(��������)
		DirectX::XMFLOAT3 pos;
		position.x = e.GetPosition().x + distXZ(mt);
		position.y = e.GetPosition().y + e.GetHeight() * 0.5f + distY(mt);
		position.z = e.GetPosition().z + distXZ(mt);
		//�^�[�Q�b�g
		target.x = sinf(e.GetAngle().y);
		target.y = 0;
		target.z = cosf(e.GetAngle().y);
		//�v���C���[���^�[�Q�b�g�ɂ���
		target.x = p.GetPosition().x;
		target.y = p.GetPosition().y + p.GetHeight() * 0.5f;
		target.z = p.GetPosition().z;
	}

	lifeTimer = lifeTimerBank;
	coolTime = coolTimeBank;

	UpdateTransform();
}
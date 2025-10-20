#include "Character.h"
#include "EnemyManager.h"
#include "RayCast.h"
#include "stage.h"
#include "KeyInput.h"

//�s��X�V����
void Character::UpdateTransfom()
{
	//�X�P�[���s�񐧍�
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	//��]�s��𐧍�
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	//�ʒu�s����쐬
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//�O�̍s���g�ݍ��킹�ă��[���h�s����쐬
	DirectX::XMMATRIX W = S * R * T;

	//�v�Z�������[���h�s������o��
	DirectX::XMStoreFloat4x4(&transform, W);
}

void Character::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	////���̃f�o�b�O
	//renderer->RenderSphere(rc, position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
	//�~���̃f�o�b�O
	renderer->RenderCylinder(rc, position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}


bool Character::ApplyDamage(float dmage, EnemyManager* enemyManager)
{
	//�_���[�W��0�̏ꍇ�͌��N��Ԃ�ύX����K�v���Ȃ�
	if (dmage == 0) return false;

	//���S���Ă���ꍇ�͌��N��Ԃ�ύX���Ȃ�
	if (HP <= 0) return false;

	//�_���[�W����
	HP -= dmage;

	if (HP == 0)
	{
		OnDead(enemyManager);
	}
	else
	{
		OnDamaged();
	}

	//���N��Ԃ�ύX�����ꍇ��true��Ԃ�
	return true;
}

bool Character::ApplyDamage(float dmage, float invincidleTime, EnemyManager* enemyManager)
{
	//�_���[�W��0�̏ꍇ�͌��N��Ԃ�ύX����K�v���Ȃ�
	if (dmage == 0) return false;

	//���S���Ă���ꍇ�͌��N��Ԃ�ύX���Ȃ�
	if (HP <= 0) return false;

	if (invincidleTimer > 0) return false;

	invincidleTimer = invincidleTime;

	//�_���[�W����
	HP -= dmage;

	if (HP == 0)
	{
		OnDead(enemyManager);
	}
	else
	{
		OnDamaged();
	}

	//���N��Ԃ�ύX�����ꍇ��true��Ԃ�
	return true;
}

//�Ռ���^����
void Character::AddImpulse(const DirectX::XMFLOAT3& impulse)
{
	velocity.x += impulse.x;
	velocity.y += impulse.y;
	velocity.z += impulse.z;
}

void Character::Move(float elapsedTime, float vx, float vz, float speed)
{
	//speed *= elapsedTime;
	//position.x += vx * speed;
	//position.z += vz * speed;

	KeyInput k;

	if (k.GetKeyDown(VK_SHIFT)&&coolTimer <= 0)
	{
		boostTimer = 0.05f;
		coolTimer = coolTime;
	}


	//�ړ������x�N�g��
	moveVecX = vx;
	moveVecZ = vz;


	if (boostTimer > 0.0f)
	{
		dash = true;
		acceleration = 200.0f;
		MaxMoveSpeed = speed * 3;
		boostTimer -= elapsedTime;
	}
	else
	{
		dash = false;
		acceleration = 50.0f;
		MaxMoveSpeed = speed;
	}
	//�ő呬�x����

	coolTimer -= elapsedTime;
}

void Character::Turn(float elapsedTime, float vx, float vz, float speed)
{
	speed *= elapsedTime;

	//�i�s�x�N�g�����[���x�N�g���̏ꍇ�͏�������K�v�Ȃ�
	float length = sqrtf(vx * vx + vz * vz);
	if (length == 0) return;

	//�P�ʃx�N�g����
	vx /= length;
	vz /= length;

	//���g�̉�]�l����O���������߂�
	float frontX = sinf(angle.y);
	float frontZ = cosf(angle.y);

	//��]�p�����߂邽�߁A��̒P�ʃx�N�g���̓��ς��v�Z����
	float dot = (frontX * vx) + (frontZ * vz);

	//�Ȃ��Ȓl��-1.0�`1.0�ŕ\������Ă���A��̒P�ʃx�N�g���̊p�x��
	//�������ق�1.0�ɋ߂Â��Ƃ��������𗘗p���ĉ�]���x�𒲐߂���
	float rot = 1.0 - dot;
	if(rot > speed) rot = speed;

	//���E������s�����߂ɓ�̒P�ʃx�N�g���̊O�ς��v�Z����
	float cross = (frontZ * vx) - (frontX * vz);

	//2D�̊O�ς����̏ꍇ�����̏ꍇ�ɂ���č��E������s����
	//���E������s�����Ƃɂ���č��E��]��I������
	if (cross < 0.0f)
	{
		angle.y -= rot;
	}
	else
	{
		angle.y += rot;
	}

}

void Character::Jump(float speed)
{
	velocity.y = speed;
}

void Character::UpdateVelocity(float elapsedTime, const Stage* stage)
{

	//�������͍X�V
	UpdateVerticalVelocity(elapsedTime);

	//�������͍X�V����
	UpdateHorizontalVelocity(elapsedTime);

	//�����ړ��X�V����
	UpdateVerticalMove(elapsedTime,stage);

	//�����ړ��X�V����
	UpdateHorizontalMove(elapsedTime,stage);

	{
	////�d�͏���
	//velocity.y += gravity * elapsedTime;

	////�ړ�����
	//position.y += velocity.y * elapsedTime;

	////�n�ʔ���
	//if (position.y < 0.0f)
	//{
	//	position.y = 0.0f;
	//	velocity.y = 0.0f;
	//	if (isGround == false)
	//	{
	//		isGround = true;
	//		OnLanding();
	//	}
	//}
	//else
	//{
	//	isGround = false;
	//}
	}
}


//���͍X�V
void Character::UpdateVerticalVelocity(float elapsedTime)
{
	//�d�͏���
	velocity.y += gravity * elapsedTime;

}

//�����ړ��X�V����
void Character::UpdateVerticalMove(float elapsedTime,const Stage* stage)
{
	//�ړ�����
	float MoveY = velocity.y * elapsedTime;

	position.y += MoveY;

	//�n�ʔ���
	if (position.y < 0.0f)
	{
		position.y = 0.0f;
		velocity.y = 0.0f;
		if (isGround == false)
		{
			isGround = true;
			OnLanding();
		}
	}
	else
	{
		isGround = false;
	}

}

void Character::UpdateHorizontalVelocity(float elapsedTime)
{
	//XZ���ʂ̑��͂���������
	float length = sqrtf( velocity.x * velocity.x + velocity.z * velocity.z);
	float friction = this->friction * elapsedTime;
	if (moveVecX == 0.0f && moveVecZ == 0.0f)
	{
		friction *= 5.0f; // ���͂��Ȃ��Ƃ��͖��C������
	}

	if (length > 0.0f)
	{
		//���C��

		//�󒆂ɂ���Ԃ͖��C�͂����炷
		if (isGround == false) friction *= airControl;

		//���C�ɂ�鉡�����̌�������
		if (length > friction)
		{
			//if (isGround)
			//{
			//	velocity.x -= friction;
			//	velocity.z -= friction;
			//}
			float vx = velocity.x / length;
			float vz = velocity.z / length;
			velocity.x = vx * (length - friction);
			velocity.z = vz * (length - friction);
		}
		//�������̑��͂����C�͂����ɂȂ����瑬�͂𖳌���
		else
		{
			velocity.x = 0.0f;
			velocity.z = 0.0f;
		}
	}

	//XZ���ʂ̑��͂���������
	if (length <= MaxMoveSpeed)
	{
		//�ړ��x�N�g�����[���łȂ��Ȃ�
		float moveVecLength = sqrtf(moveVecX * moveVecX + moveVecZ * moveVecZ);
		if (moveVecLength > 0.0f)
		{
			//������
			float acceleration = this->acceleration * elapsedTime;

			if (isGround == false) acceleration *= airControl;

			//�ړ��x�N�g���ɂ���������
			velocity.x += (moveVecX / moveVecLength) * acceleration;
			velocity.z += (moveVecZ / moveVecLength) * acceleration;

			//�ő�����x����
			{
				float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
				if (length > MaxMoveSpeed)
				{
					velocity.x = (velocity.x / length) * MaxMoveSpeed;
					velocity.z = (velocity.z / length) * MaxMoveSpeed;
				}
			}
		}
	}
	//�ړ��x�N�g�������Z�b�g
	moveVecX = 0;
	moveVecZ = 0;
}

void Character::UpdateHorizontalMove(float elapsedTime, const Stage* stage)
{
	position.x += velocity.x * elapsedTime;
	position.z += velocity.z * elapsedTime;
}

//���G����
void Character::UpdateInvincidleTimer(float elapsedTime)
{
	if (invincidleTimer > 0.0f)
	{
		invincidleTimer -= elapsedTime;
	}
}

void Character::HitImpact(DirectX::XMFLOAT3 thisPos, DirectX::XMFLOAT3 targetPos, float power, Character* Target)
{
	//������΂�
	DirectX::XMFLOAT3 impulse;
	DirectX::XMVECTOR ThisPos = DirectX::XMLoadFloat3(&thisPos);
	DirectX::XMVECTOR TargetPos = DirectX::XMLoadFloat3(&targetPos);
	DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(TargetPos, ThisPos);
	//�P�ʉ�
	Vec = DirectX::XMVector3Normalize(Vec);
	//�X���J�[�{����
	DirectX::XMStoreFloat3(&impulse, Vec);
	impulse.x *= power;
	impulse.y += 0;
	impulse.z *= power;

	Target->AddImpulse(impulse);

	//�q�b�g�G�t�F�N�g
	DirectX::XMFLOAT3 e = Target->GetPosition();
	e.y += Target->GetHeight() * 0.5;
	//hitEffect->Play(e);

	////�q�b�gSE�Đ�
	//hitSE->Play(false);
}

#pragma once

#include <DirectXMath.h>
#include "System/ShapeRenderer.h"

class EnemyManager;
class Stage;

//�L�����N�^�[
class Character
{
protected:

	//�d��
	float gravity = -30.0f;
	DirectX::XMFLOAT3 velocity = { 0,0,0 };

	//���C
	float friction = 15.0f;

protected:
	DirectX::XMFLOAT3	position  = { 0,0,0 };
	DirectX::XMFLOAT3	angle     = { 0,0,0 };
	DirectX::XMFLOAT3	scale     = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = {
		//�X�P�[��x
		1, 0, 0, 0,
		//�X�P�[��y
		0, 1, 0, 0,
		//��]
		0, 0, 1, 0,
		//�ʒu
		0, 0, 0, 1
	};

	//���a
	float radius = 0.5f;

	//���n����
	bool isGround = false;

	//����
	float height = 2.0f;

	//HP
	float HP = 5;

	//���G����
	float invincidleTimer = 1.0;

	//�����x
	float acceleration = 50.0f;
	//�X�s�[�h����l
	float MaxMoveSpeed = 5.0f;
	//�ړ�����X
	float moveVecX = 0.0f;
	//�ړ�����Z
	float moveVecZ = 0.0f;
	//�󒆐���
	float airControl = 0.3f;
	//�ǂꂾ���������邩�H
	float downhillOffset = 43.0f;

public:
	Character() {}
	virtual ~Character() {}

public:

	/////////////////////////////////////////////

	//�ʒu�擾
	const DirectX::XMFLOAT3& GetPosition() const        { return position; }

	//�ʒu�ݒ�
	void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }

	//��]�擾
	const DirectX::XMFLOAT3& GetAngle() const           { return angle; }

	//��]�ݒ�
	void SetAngle(const DirectX::XMFLOAT3& angle)       { this->angle = angle; }

	//�X�P�[���擾
	const DirectX::XMFLOAT3& GetScale() const           { return scale; }

	//�X�P�[���擾
	void SetScale(const DirectX::XMFLOAT3& scale)       { this->scale = scale; }

	//���a�擾
	float GetRadius() const { return radius; }

	//�����擾
	float GetHeight() const { return height; }

	//HP�擾
	float GetHP() const { return HP; }
	
	/////////////////////////////////////////////

public:
	//�s�񏈗�
	void UpdateTransfom();

	//�f�o�b�O�s���~�e�B�u�`��
	virtual void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	//�n�ʂɐڂ��Ă��邩
	bool IsGround() const { return isGround; };

	//�_���[�W��^����
	bool ApplyDamage(float dmage, EnemyManager* enemyManager);

	//�_���[�W��^����
	bool ApplyDamage(float dmage ,float invincidleTime, EnemyManager* enemyManager);

	//�_���[�W��^����
	virtual bool ApplyDamage(float dmage, float invincidleTime) { return false; };

	//������΂�
	void HitImpact(DirectX::XMFLOAT3 thisPos,DirectX::XMFLOAT3 targetPos,float power,Character* Target);

	//�Ռ���^����
	void AddImpulse(const DirectX::XMFLOAT3& impulse);

protected:
	//�������͍X�V
	void UpdateVerticalVelocity(float elapsedTime);

	//�����ړ��X�V����
	virtual void UpdateVerticalMove(float elapsedTime, const Stage* stage);

	//�������͍X�V����
	void UpdateHorizontalVelocity(float elapsedTime);

	//�����ړ��X�V����
	virtual void UpdateHorizontalMove(float elapsedTime, const Stage* stage);

	//���͏����X�V
	void UpdateVelocity(float elapsedTime, const Stage* stage);

protected:

	//�ړ�����
	void Move(float elapsedTime, float vx, float vz, float speed);

	//���񏈗�
	void Turn(float elapsedTime, float vx, float vz, float speed);

	//�W�����v
	void Jump(float speed);

	//���n�����ƂɌĂ΂��
	virtual void OnLanding() {}

	//�_���[�W���󂯂����ɌĂ΂��
	virtual void OnDamaged() {}

	//���S�����Ƃ��ɌĂ΂��
	virtual void OnDead(EnemyManager* enemyManager){}

	//���G���ԍX�V
	void UpdateInvincidleTimer(float elapsedTime);
};
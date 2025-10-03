#pragma once

#include "System/Model.h"
#include "Enemy.h"
#include "WeaponManager.h"

class Player;

class EnemyBoss : public Enemy
{
public:
	EnemyBoss();
	~EnemyBoss()override;

	void Update(float elapsedTime, Player* player, const Stage& stage, EnemyManager* enemyManager) override;

	void Render(const RenderContext& rc, ModelRenderer* renderer) override;

	//�f�o�b�O�v���~�e�B�u�`��
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer) override;

	//�꒣��ݒ�
	void SetTerritory(const DirectX::XMFLOAT3& origin, float range);

protected:
	//���S�������ɌĂ΂��
	void OnDead(EnemyManager* enemyManager) override;

private:

	//�o�~�X�e�[�g�֑J��
	void SetEanderState();

	//�ҋ@�X�e�[�g���x�J��
	void SetIdleaState();

	//�U���X�e�[�g�֑J��
	void SetAttackState(Player* player);

	//�����X�e�[�g
	void SetSummonEnemy(Player* player);

	//���[�v�X�e�[�g���x�J��
	void SetWarpState();

	//�v���C���[�{��
	bool SearchPlayer(Player* player);

	//�ǂ̃]�[���Ƀv���C���[�����邩
	bool SearchPlayerZone(Player* player,float start,float end);

	//�n�C�����X�e�[�g�X�V����
	void UpdatWanderState(float elapsedTime, Player* player);

	//����X�e�[�g�ւǂ�
	void UpdatetIdleState(float elaspedTime, Player* player);

	//�U���X�e�[�g�X�V����
	void UpdateAttackState(float elapsedTime, Player* player);

	//�����X�e�[�g
	void UpdateSummonEnemyState(float elapsedTime, Player* player);

	//���[�v�X�e�[�g�X�V����
	void UpdateWarpState(float elapsedTime, Player* player);

	//�^�[�Q�b�g�ʒu�������_����
	void SetRandomTargetPosition(float start, float end);

	//�ڕW�n�_�ֈړ�
	void MoveToTarget(float elapsedTime, float moveSpeedRate, float turnSpeedRate,const DirectX::XMFLOAT3& Pos);

	//���������G�l�~�[�ƒe�̓����蔻��
	void CollisionSummonEnemyVsBullet(Weapon* w, Effect* hitEffect, AudioSource* hitSE) override;

	//�v���C���[�ƒe�̓����蔻��
	void CollisionPlayerVsBullet(Player* p) override;

private:
	//�X�e�[�g
	enum class State
	{
		Wander,
		Idle,
		Attack,
		SummonEnemy,
		Warp,
	};


private:
	std::unique_ptr<Model> model = nullptr;

	State state = State::Wander;
	DirectX::XMFLOAT3 targetPositon = { 0,0,0 };
	DirectX::XMFLOAT3 territoryOrigin = { 0,0,0 };
	float moveTerritory = 7.0f;
	float summonTerritory = moveTerritory + 5.0f;
	//���[�v����͈�
	float warpTerritory = summonTerritory + 5.0f;
	float moveSpeed = 5.0;
	float turnSpeed = DirectX::XMConvertToRadians(360);

	float stateTimer = 0.0f;

	DirectX::XMFLOAT3 SummonPos[2];

	//float searchRange = 20.0f;
	std::unique_ptr<WeaponManager> weaponManager;
	std::unique_ptr<EnemyManager> em;
};
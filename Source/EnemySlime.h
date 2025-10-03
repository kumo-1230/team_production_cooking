#pragma once

#include "System/Model.h"
#include "Enemy.h"
#include "WeaponManager.h"

class Player;

class EnemySlime : public Enemy
{
private:
	std::unique_ptr<Model> model = nullptr;

	DirectX::XMFLOAT3 targetPositon = { 0,0,0 };
	DirectX::XMFLOAT3 territoryOrigin = { 0,0,0 };
	float moveSpeed = 2.0;
	float turnSpeed = DirectX::XMConvertToRadians(360);

	float stateTimer = 0.0f;

	float searchRange = 5.0f;
	std::unique_ptr<WeaponManager> weaponManager;
	std::unique_ptr<EnemyManager> em;

public:
	EnemySlime();
	~EnemySlime()override;
private:

	//�ڕW�n�_�ֈړ�
	void MoveToTarget(float elapsedTime, float moveSpeedRate, float turnSpeedRate);

	//�v���C���[�ƒe�̓����蔻��
	void CollisionPlayerVsBullet(Player* p) override;

public:

	void Update(float elapsedTime,Player* player, const Stage* stage, EnemyManager* enemyManager) override;

	void Render(const RenderContext& rc, ModelRenderer* renderer) override;

	//�f�o�b�O�v���~�e�B�u�`��
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer) override;

protected:
	//���S�������ɌĂ΂��
	void OnDead(EnemyManager* enemyManager) override;

};
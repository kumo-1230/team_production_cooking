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

	//デバッグプリミティブ描画
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer) override;

	//縄張り設定
	void SetTerritory(const DirectX::XMFLOAT3& origin, float range);

protected:
	//死亡した時に呼ばれる
	void OnDead(EnemyManager* enemyManager) override;

private:

	//俳諧ステートへ遷移
	void SetEanderState();

	//待機ステート干支遷移
	void SetIdleaState();

	//攻撃ステートへ遷移
	void SetAttackState(Player* player);

	//召喚ステート
	void SetSummonEnemy(Player* player);

	//ワープステート干支遷移
	void SetWarpState();

	//プレイヤー捜索
	bool SearchPlayer(Player* player);

	//どのゾーンにプレイヤーがいるか
	bool SearchPlayerZone(Player* player,float start,float end);

	//ハイかいステート更新処理
	void UpdatWanderState(float elapsedTime, Player* player);

	//特定ステートへどう
	void UpdatetIdleState(float elaspedTime, Player* player);

	//攻撃ステート更新処理
	void UpdateAttackState(float elapsedTime, Player* player);

	//召喚ステート
	void UpdateSummonEnemyState(float elapsedTime, Player* player);

	//ワープステート更新処理
	void UpdateWarpState(float elapsedTime, Player* player);

	//ターゲット位置をランダム化
	void SetRandomTargetPosition(float start, float end);

	//目標地点へ移動
	void MoveToTarget(float elapsedTime, float moveSpeedRate, float turnSpeedRate,const DirectX::XMFLOAT3& Pos);

	//召喚したエネミーと弾の当たり判定
	void CollisionSummonEnemyVsBullet(Weapon* w, Effect* hitEffect, AudioSource* hitSE) override;

	//プレイヤーと弾の当たり判定
	void CollisionPlayerVsBullet(Player* p) override;

private:
	//ステート
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
	//ワープする範囲
	float warpTerritory = summonTerritory + 5.0f;
	float moveSpeed = 5.0;
	float turnSpeed = DirectX::XMConvertToRadians(360);

	float stateTimer = 0.0f;

	DirectX::XMFLOAT3 SummonPos[2];

	//float searchRange = 20.0f;
	std::unique_ptr<WeaponManager> weaponManager;
	std::unique_ptr<EnemyManager> em;
};
#pragma once

#include "System/ModelRenderer.h"
#include "Character.h"
#include "Effect.h"
#include "System/AudioSource.h"
#include "Camera.h"
#include <memory>
#include "StageManager.h"

//プレイヤー
class Player : public Character
{
private:
	std::unique_ptr<Model> model = nullptr;
	float moveSpeed = 5.0f;

	float turnSpeed = DirectX::XMConvertToRadians(720);

	float jumpSpeed = 12.0f;

	int jumpCount = 0;
	int jumpLimit = 2;

	DirectX::XMFLOAT3 p, l;

	Effect* hitEffect = nullptr;

	AudioSource* hitSE = nullptr;

private:
	//Player();
	//~Player() override;
public:
	Player();
	~Player() override;

	//初期化
	void Initialize();

	//終了化
	void Finalize();

public:
	//更新処理
	void Update(float elapsedTime,const Camera* camera, EnemyManager* enemyManager, const StageManager* stage);

	//描画処理
	void Render(const RenderContext& rc, ModelRenderer* render);

	//デバッグ用GUI描画
	void DrawDebugGUI();

	//デバッグプリミティブ描画
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	bool ApplyDamage(float dmage, float invincidleTime)override;

protected:
	//着地したときに呼ばれる
	void OnLanding() override;

private:
	//スティック入力値から移動ベクトルを取得
	DirectX::XMFLOAT3 GetMoveVec(const Camera& camera) const;

private:

	//移動入力処理
	void InputMove(float elapsedTime, const Camera* camera);
	//ジャンプ入力処理
	void InputJump();

	void UpdateHorizontalMove(float elapsedTime, const Stage* stage) override;

	void UpdateVerticalMove(float elapsedTime, const Stage* stage) override;

	//弾丸入力処理
	void InputProjectile(EnemyManager* enemyManager);

	//プレイヤーとエネミーとの衝突処理
	void CollisionPlayerVsEnemies(EnemyManager* enemyManager);

};
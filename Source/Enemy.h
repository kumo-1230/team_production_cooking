#pragma once

#include "System/ModelRenderer.h"
#include "Character.h"
#include "Effect.h"
#include "System/AudioSource.h"
#include "System/Audio.h"
#include <memory>

class EnemyManager;
class Player;
class Weapon;

class Enemy : public Character
{
protected:
	float lifeTimer = 5.0f;
	std::unique_ptr<Effect> hitEffect;
	std::shared_ptr<AudioSource> hitSE;

public:
	Enemy() {}
	~Enemy() override {}

public:

	//更新処理
	virtual void Update(float elapsedTime, Player* player, const Stage* stage, EnemyManager* enemyManager) = 0;

	//描画処理
	virtual void Render(const RenderContext& rc, ModelRenderer* render) = 0;

	//デバッグプリミティブ描画
	virtual void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer) {};

	//廃棄
	void Destroy(EnemyManager* enemyManager);

	float GetLifeTimer() { return lifeTimer; }

	//召喚したエネミーと弾の当たり判定
	virtual void CollisionSummonEnemyVsBullet(Weapon* w, Effect* hitEffect, AudioSource* hitSE) {}

	virtual void CollisionPlayerVsBullet(Player* p){}

};
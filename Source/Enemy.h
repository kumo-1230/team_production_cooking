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

	//�X�V����
	virtual void Update(float elapsedTime, Player* player, const Stage* stage, EnemyManager* enemyManager) = 0;

	//�`�揈��
	virtual void Render(const RenderContext& rc, ModelRenderer* render) = 0;

	//�f�o�b�O�v���~�e�B�u�`��
	virtual void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer) {};

	//�p��
	void Destroy(EnemyManager* enemyManager);

	float GetLifeTimer() { return lifeTimer; }

	//���������G�l�~�[�ƒe�̓����蔻��
	virtual void CollisionSummonEnemyVsBullet(Weapon* w, Effect* hitEffect, AudioSource* hitSE) {}

	virtual void CollisionPlayerVsBullet(Player* p){}

};
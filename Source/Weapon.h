#pragma once

#include "System/ModelRenderer.h"
#include "System/ShapeRenderer.h"
#include <memory>
#include <functional>

enum WEAPON
{
	BULLET_STRAIGHT = 0,
	BULLET_HOMING,
	ROTATION,
	BULLET_RANDOM,
	SWORD,
	BOOMERANG,
	STOP,
};

enum LCHAR
{
	PLAYER = 0,
	ENEMY,
};

class Player;
class EnemyManager;
class Enemy;

class Weapon
{
protected:
	DirectX::XMFLOAT3 position = { 0,0,0 };
	DirectX::XMFLOAT3 direction = { 0,0,1 };
	DirectX::XMFLOAT3 scale = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1,
	};

	float radius = 0.5f;

	int weaponMode;
	float coolTime;
	float coolTimeBank;
	std::unique_ptr<Model> model;
	int Lv;
	bool invisibule = false;
	float lifeTimer;
	float lifeTimerBank;

	float attackPower = 0.5f;

	int Start = 0;

public:
	Weapon(int mode);
	virtual ~Weapon() {}

public:

	///////////////////////////////////////////////
	
	//�ʒu�擾
	const DirectX::XMFLOAT3& GetPosition() const { return position; }

	//�����擾
	const DirectX::XMFLOAT3& GetDirention() const { return direction; }

	//�X�P�[���擾
	const DirectX::XMFLOAT3& GetScale() const { return scale; }

	//���a�擾
	float GetRadius() const { return radius; }

	//���Ԏ擾
	float GetLifeTimer() const { return lifeTimer; }

	//�������ǂ���
	bool GetInvisibule() const { return invisibule; }
	void SetInvisibule() { invisibule = false; }

	float GetCoolTime() { return coolTime; }
	void SetCoolTime() { coolTime = coolTimeBank; }

	void SetLifeTimer() { lifeTimer = lifeTimerBank; }

	int GetStart() { return Start; }

	void AddStart() { Start++; }

	int GetWeaponMode() { return weaponMode; }

	virtual void SetOffset(DirectX::XMFLOAT3 of) {}

	float GetAttackPower() { return attackPower; }

	///////////////////////////////////////////////

public:

	//�X�V����
	virtual void Update(float elapsedTime);
	virtual void Update(float elapsedTime, const DirectX::XMFLOAT3& pos);

	//�`�揈��
	virtual void Render(const RenderContext& rc, ModelRenderer* mr);

	//�f�o�b�O�v���~�e�B�u�`��
	virtual void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	//�p��
	void Destroy();

	void CoolTimeDown(float elapsedTime);

	virtual void Launch(const Player& p, const EnemyManager& em, const Enemy& e, int lanchChar);

protected:
	//�s��X�V����
	void UpdateTransform();

};
#pragma once

#include "Weapon.h"

class BulletRotate : public Weapon
{
private:
	DirectX::XMFLOAT3 offset = { 0,0,0 };
	DirectX::XMFLOAT3 CPos = { 0,0,0 }; //�v���C���[�̃|�W�V����
	float turnSpeed;
	float angle;

public:
	BulletRotate(int Lv);
	~BulletRotate() override;

	//�X�V����
	void Update(float elapsedTime, const DirectX::XMFLOAT3& pos) override;

	void InitializeLv1();
	void InitializeLv2();
	void InitializeLv3();
	void InitializeLv4();
	void InitializeLv5();

	//����
	void Launch(const Player& p, const EnemyManager& em, const Enemy& e, int lanchChar) override;

	///////////////////////

	void SetOffset(DirectX::XMFLOAT3 of) override { offset = of; }

};
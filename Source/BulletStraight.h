#pragma once

#include "Weapon.h"

//���i�e��
class BulletStraight :public Weapon
{
private:
	float speed;

public:
	//ProjectileStraight();
	BulletStraight(int Lv);
	~BulletStraight() override;

	void InitializeLv1();
	void InitializeLv2();
	void InitializeLv3();
	void InitializeLv4();
	void InitializeLv5();

	//�X�V����
	void Update(float elapsedTime) override;

	//����
	void Launch(const Player& p, const EnemyManager& em, const Enemy& e, int lanchChar) override;

};
#pragma once

#include "Weapon.h"

//íºêiíeä€
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

	//çXêVèàóù
	void Update(float elapsedTime) override;

	//î≠éÀ
	void Launch(const Player& p, const EnemyManager& em, const Enemy& e, int lanchChar) override;

};
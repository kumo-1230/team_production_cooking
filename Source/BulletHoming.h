#pragma once

#include "Weapon.h"

//í«îˆíeä€
class BulletHoming : public Weapon
{
private:
	DirectX::XMFLOAT3 target = { 0,0,0 };
	float moveSpeed;
	float turnSpeed = DirectX::XMConvertToRadians(180);

	std::function<void()> func[5] =
	{
		[this] { this->InitializeLv1(); },
		[this] { this->InitializeLv2(); },
		[this] { this->InitializeLv3(); },
		[this] { this->InitializeLv4(); },
		[this] { this->InitializeLv5(); }, 
	};

public:
	BulletHoming(int Lv);
	~BulletHoming() override;

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
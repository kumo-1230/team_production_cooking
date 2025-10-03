#include "BulletStraight.h"
#include "Player.h"
#include "EnemyManager.h"
#include <random>

BulletStraight::BulletStraight(int Lv) : Weapon(WEAPON::BULLET_STRAIGHT)
{
	model.reset(new Model("Data/Model/Sword/Sword.mdl"));

	//表示サイズを調節
	scale.x = scale.y = scale.z = 3.0f;

	switch (Lv)
	{
	case 1:
		InitializeLv1();
		break;
	case 2:
		InitializeLv2();
		break;
	case 3:
		InitializeLv3();
		break;
	case 4:
		InitializeLv4();
		break;
	case 5:
		InitializeLv5();
		break;
	}
	coolTimeBank = coolTime;
	lifeTimerBank = lifeTimer;
}

BulletStraight::~BulletStraight()
{
}

void BulletStraight::InitializeLv1()
{
	lifeTimer = 1.0f;
	coolTime = 0.5f;
	speed = 10.0f;
}

void BulletStraight::InitializeLv2()
{
	lifeTimer = 1.0f;
	coolTime = 0.3f;
	speed = 20.0f;
}

void BulletStraight::InitializeLv3()
{
	lifeTimer = 1.0f;
	coolTime = 0.2f;
	speed = 30.0f;
}

void BulletStraight::InitializeLv4()
{
	lifeTimer = 1.0f;
	coolTime = 0.1f;
	speed = 40.0f;
}

void BulletStraight::InitializeLv5()
{
	lifeTimer = 1.0f;
	coolTime = 0.1f;
	speed = 50.0f;
}


void BulletStraight::Update(float elapsedTime)
{
	//寿命更新
	lifeTimer -= 1 * elapsedTime;
	if (lifeTimer < 0)
	{
		//自分削除
		Destroy();
	}

	//移動
	float speed = this->speed * elapsedTime;
	position.x += direction.x * speed;
	position.y = position.y;
	position.z += direction.z * speed;

	//オブジェクト行列更新
	UpdateTransform();

	//モデル行列更新処理
	model->UpdateTransform();
}

void BulletStraight::Launch(const Player& p, const EnemyManager& em, const Enemy& e, int lanchChar)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> distXZ(-1.0f, 1.0f);

	if (lanchChar == LCHAR::PLAYER)
	{
		//前方向
		direction.x = std::sinf(p.GetAngle().y);
		direction.y = 0;
		direction.z = std::cosf(p.GetAngle().y);
		//発射位置(腰当たり)
		position.x = p.GetPosition().x + distXZ(mt);
		position.y = p.GetPosition().y + p.GetHeight() * 0.5f;
		position.z = p.GetPosition().z + distXZ(mt);
	}
	else if (lanchChar == LCHAR::ENEMY)
	{
		//前方向
		direction.x = std::sinf(e.GetAngle().y);
		direction.y = 0;
		direction.z = std::cosf(e.GetAngle().y);
		//発射位置(腰当たり)
		position.x = e.GetPosition().x + distXZ(mt);
		position.y = e.GetPosition().y + e.GetHeight() * 0.5f;
		position.z = e.GetPosition().z + distXZ(mt);
	}

	lifeTimer = lifeTimerBank;
	coolTime = coolTimeBank;

	UpdateTransform();
}
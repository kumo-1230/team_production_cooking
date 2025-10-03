#include "BulletRotate.h"
#include "Player.h"
#include "EnemyManager.h"

BulletRotate::BulletRotate(int Lv) :Weapon(WEAPON::ROTATION)
{
	model.reset(new Model("Data/Model/Sword/Sword.mdl"));

	//スケーリング
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

BulletRotate::~BulletRotate()
{
}

void BulletRotate::InitializeLv1()
{
	lifeTimer = 3.0f;
	coolTime = 1.0f;
	turnSpeed = DirectX::XMConvertToRadians(180);
}

void BulletRotate::InitializeLv2()
{
	lifeTimer = 3.5f;
	coolTime = 0.8f;
	turnSpeed = DirectX::XMConvertToRadians(200);
}

void BulletRotate::InitializeLv3()
{
	lifeTimer = 4.0f;
	coolTime = 0.6f;
	turnSpeed = DirectX::XMConvertToRadians(220);
}

void BulletRotate::InitializeLv4()
{
	lifeTimer = 4.5f;
	coolTime = 0.4f;
	turnSpeed = DirectX::XMConvertToRadians(240);
}

void BulletRotate::InitializeLv5()
{
	lifeTimer = 5.0f;
	coolTime = 0.2f;
	turnSpeed = DirectX::XMConvertToRadians(260);
}

void BulletRotate::Update(float elapsedTime, const DirectX::XMFLOAT3& pos)
{
	//寿命更新
	lifeTimer -= 1 * elapsedTime;
	if (lifeTimer < 0)
	{
		//自分削除
		Destroy();
	}

	using namespace DirectX;

	CPos = pos;

	// 一定距離の初期オフセット（X軸に5離れた位置）
	XMVECTOR Offset = XMLoadFloat3(&offset);

	// 回転角度（時間に応じて変化させるとぐるぐる回る）
	angle += turnSpeed * elapsedTime;

	// Y軸回転のクォータニオンを作成
	XMVECTOR q = XMQuaternionRotationAxis(XMVectorSet(0, 1, 0, 0), angle);

	// クォータニオンでオフセットを回転
	XMVECTOR rotatedOffset = XMVector3Rotate(Offset, q);

	// 最終座標 = 中心 + 回転後オフセット
	XMVECTOR target = XMVectorAdd(XMLoadFloat3(&CPos), rotatedOffset);

	XMStoreFloat3(&position, target);	//オブジェクト行列を更新
	UpdateTransform();

	//モデル行列更新
	model->UpdateTransform();
}

void BulletRotate::Launch(const Player& p, const EnemyManager& em, const Enemy& e, int lanchChar)
{
	if (lanchChar == LCHAR::PLAYER)
	{
		//発射位置(腰当たり)
		position.x = p.GetPosition().x;
		position.y = p.GetPosition().y + p.GetHeight() * 0.5f;
		position.z = p.GetPosition().z;
	}
	else if (lanchChar == LCHAR::ENEMY)
	{
		//発射位置(腰当たり)
		position.x = e.GetPosition().x;
		position.y = e.GetPosition().y + e.GetHeight() * 0.5f;
		position.z = e.GetPosition().z;
	}

	lifeTimer = lifeTimerBank;
	coolTime = coolTimeBank;

	UpdateTransform();
}
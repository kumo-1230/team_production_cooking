#include "BulletHoming.h"
#include <random>
#include "Player.h"
#include "EnemyManager.h"
#include "Enemy.h"

BulletHoming::BulletHoming(int Lv) : Weapon(WEAPON::BULLET_HOMING)
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

BulletHoming::~BulletHoming()
{
}

void BulletHoming::InitializeLv1()
{
	moveSpeed = 10.0f;
	lifeTimer = 2.0f;
	coolTime = 1.0f;
}

void BulletHoming::InitializeLv2()
{
	moveSpeed = 15.0f;
	lifeTimer = 3.0f;
	coolTime = 0.8f;
}

void BulletHoming::InitializeLv3()
{
	moveSpeed = 20.0f;
	lifeTimer = 3.0f;
	coolTime = 0.6f;
}

void BulletHoming::InitializeLv4()
{
	moveSpeed = 25.0f;
	lifeTimer = 3.0f;
	coolTime = 0.4f;
}

void BulletHoming::InitializeLv5()
{
	moveSpeed = 30.0f;
	lifeTimer = 3.0f;
	coolTime = 0.2f;
}

void BulletHoming::Update(float elapsedTime)
{
	//寿命更新
	lifeTimer -= 1 * elapsedTime;
	if (lifeTimer < 0)
	{
		//自分削除
		Destroy();
	}

	//移動
	float speed = this->moveSpeed * elapsedTime;
	position.x += direction.x * speed;
	position.y += direction.y * speed;
	position.z += direction.z * speed;

	//旋回
	float turnS = this->turnSpeed * elapsedTime;

	//ターゲットまでのベクトルを算出
	DirectX::XMVECTOR Position = DirectX::XMLoadFloat3(&position);
	DirectX::XMVECTOR Target = DirectX::XMLoadFloat3(&target);
	DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Target, Position);

	//ゼロベクトルでないなら回転処理
	DirectX::XMVECTOR Lengthsq = DirectX::XMVector3Length(Vec);
	float lengthSq;
	DirectX::XMStoreFloat(&lengthSq, Lengthsq);
	if (lengthSq > 0.00001f)
	{
		//ターゲットまでのベクトルを単位ベクトル化
		Vec = DirectX::XMVector3Normalize(Vec);

		//向いてる方向ベクトルを算出
		DirectX::XMVECTOR Direction = DirectX::XMLoadFloat3(&direction);

		//前方向ベクトルとターゲットまでの内積を算出
		DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(Direction, Vec);

		float dot;
		//DirectX::XMStoreFloat(&dot, Dot);
		dot = DirectX::XMVectorGetX(Dot);

		//ない席値は-1.0～1.0で表現されており、二つの単位ベクトルの角度が
		//小さいほど1.0に近づくという性質を利用して回転速度を調節する
		float rot = acosf(dot);
		if (rot > turnS) rot = turnS;

		//回転角度があるなら回転処理をする
		if (fabsf(rot) > 0.0001f)
		{
			//回転軸を算出(外積)
			DirectX::XMVECTOR Axis = DirectX::XMVector3Cross(Direction, Vec);
			Axis = DirectX::XMVector3Normalize(Axis);

			//回転軸と回転量から回転行列を算出(クォータニオン)
			DirectX::XMVECTOR Rotation = DirectX::XMQuaternionRotationAxis(Axis, rot);

			//現在の前方向を回転させる
			Direction = DirectX::XMVector3Rotate(Direction, Rotation);

			//変換
			DirectX::XMStoreFloat3(&direction, Direction);
		}
	}
	//オブジェクト行列を更新
	UpdateTransform();

	//モデル行列更新
	model->UpdateTransform();
}

void BulletHoming::Launch(const Player& p, const EnemyManager& em, const Enemy& e, int lanchChar)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> distXZ(-3.0f, 3.0f);
	std::uniform_int_distribution<> distY(0.5f, 3.0f);

	if (lanchChar == LCHAR::PLAYER)
	{
		//前方向
		DirectX::XMFLOAT3 dir;
		direction.x = sinf(p.GetAngle().y);
		direction.y = 0;
		direction.z = cosf(p.GetAngle().y);
		//発射位置(腰当たり)
		DirectX::XMFLOAT3 pos;
		position.x = p.GetPosition().x + distXZ(mt);
		position.y = p.GetPosition().y + p.GetHeight() * 0.5f + distY(mt);
		position.z = p.GetPosition().z + distXZ(mt);
		//ターゲット
		target.x = sinf(p.GetAngle().y);
		target.y = 0;
		target.z = cosf(p.GetAngle().y);
		//一番近くの敵をターゲットにする
		float dist = FLT_MAX;
		int enemyCount = em.GetEnemyCount();
		for (int i = 0; i < enemyCount; i++)
		{
			//XZ平面での範囲チェック
			float vx = em.GetEnemyPos(i).x - position.x;
			float vy = em.GetEnemyPos(i).y - position.y;
			float vz = em.GetEnemyPos(i).z - position.z;
			float range = sqrtf(vx * vx + vy * vy + vz * vz);
			if (range < dist)
			{
				dist = range;
				target.x = em.GetEnemyPos(i).x;
				target.y = em.GetEnemyPos(i).y + em.GetEnemyHeight(i) * 0.5f;
				target.z = em.GetEnemyPos(i).z;
			}
		}
	}
	else if (lanchChar == LCHAR::ENEMY)
	{
		//前方向
		DirectX::XMFLOAT3 dir;
		direction.x = sinf(e.GetAngle().y);
		direction.y = 0;
		direction.z = cosf(e.GetAngle().y);
		//発射位置(腰当たり)
		DirectX::XMFLOAT3 pos;
		position.x = e.GetPosition().x + distXZ(mt);
		position.y = e.GetPosition().y + e.GetHeight() * 0.5f + distY(mt);
		position.z = e.GetPosition().z + distXZ(mt);
		//ターゲット
		target.x = sinf(e.GetAngle().y);
		target.y = 0;
		target.z = cosf(e.GetAngle().y);
		//プレイヤーをターゲットにする
		target.x = p.GetPosition().x;
		target.y = p.GetPosition().y + p.GetHeight() * 0.5f;
		target.z = p.GetPosition().z;
	}

	lifeTimer = lifeTimerBank;
	coolTime = coolTimeBank;

	UpdateTransform();
}
#include "EnemySlime.h"
#include "mathUtils.h"
#include "Player.h"
#include "EnemyManager.h"
#include <random>
#include "Collision.h"


EnemySlime::EnemySlime()
{
	model.reset(new Model("Data/Model/Slime/Slime.mdl"));
	em.reset(new EnemyManager());
	//スケーリング
	scale.x = scale.y = scale.z = 0.01f;

	weaponManager.reset(new WeaponManager());

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> mode(0,3);
	std::uniform_int_distribution<> Lv(0,3);

	weaponManager->SetWeaponBild(mode(rd), Lv(rd));

	weaponManager->SetWeapon();

	//幅高さ設定
	radius = 0.5f;
	height = 1.0f;
	hitEffect.reset(new Effect("Data/Effect/Hit.efk"));

	//ヒットSE読み込み
	hitSE.reset(Audio::Instance().LoadAudioSource("Data/Sound/Hit.wav"));

}

EnemySlime::~EnemySlime()
{
}

void EnemySlime::Update(float elapsedTime,Player* player, const Stage* stage,EnemyManager* enemyManager)
{
	lifeTimer = 1;
	lifeTimer -= 1 * elapsedTime;

	targetPositon = player->GetPosition();

	MoveToTarget(elapsedTime, 1.0f, 1.0f);

	//速力処理更新
	UpdateVelocity(elapsedTime,stage);

	DirectX::XMFLOAT3 outPosition;
	if (Collision::IntersectCylinderVsCylinder(
		position, radius, height,
		player->GetPosition(), player->GetRadius(), player->GetHeight(),
		outPosition))
	{
		if (player->ApplyDamage(1.0f, 0.5f))
		{
			HitImpact(position, player->GetPosition(), 5.0f, player);
			Destroy(enemyManager);
		}
	}

	//弾丸更新処理
	weaponManager->Update(elapsedTime, *player, *em.get(), *this, LCHAR::ENEMY);

	//無敵時間更新
	UpdateInvincidleTimer(elapsedTime);

	//オブジェクト行列更新
	UpdateTransfom();

	//モデル行列更新
	model->UpdateTransform();
}

void EnemySlime::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);
	//弾丸描画
	//projectileManager.Render(rc, renderer);
	weaponManager->Render(rc, renderer);
}

void EnemySlime::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	//基底クラスのデバッグプリミティブ描画
	Enemy::RenderDebugPrimitive(rc, renderer);
	//ターゲット位置をデバッグ
	renderer->RenderSphere(rc, targetPositon, 1.0f, DirectX::XMFLOAT4(1, 1, 0, 1));
	//捜索範囲をデバッグ円柱描画
	renderer->RenderCylinder(rc, position, searchRange, 1.0f, DirectX::XMFLOAT4(1, 0, 0, 1));
}

//死亡した時に呼ばれる
void EnemySlime::OnDead(EnemyManager* enemyManager)
{
	//自身を削除
	//delete this;
	Destroy(enemyManager);
}

//目的地へ移動
void EnemySlime::MoveToTarget(float elapsedTime, float moveSpeedRate, float turnSpeedRate)
{
	//ターゲット方向への進行ベクトルを算出
	float vx = targetPositon.x - position.x;
	float vz = targetPositon.z - position.z;
	float dist = sqrtf(vx * vx + vz * vz);
	//正規化
	vx /= dist;
	vz /= dist;

	//移動処理
	Move(elapsedTime, vx, vz, moveSpeed * moveSpeedRate);
	Turn(elapsedTime, vx, vz, turnSpeed * turnSpeedRate);
}

//召喚したエネミーと弾の当たり判定
void EnemySlime::CollisionPlayerVsBullet(Player* p)
{
	//すべての弾丸とすべてのプレイヤーを総当たりで衝突処理
	int weaponCount = weaponManager->GetWeaponCount();
	for (int i = 0; i < weaponCount; i++)
	{
		Weapon* weapon = weaponManager->GetWeaponIndex(i);
		if (weapon->GetInvisibule() == false)
		{
			//衝突処理
			DirectX::XMFLOAT3 outPosition;
			if (Collision::IntersectSphereVsCylinder(
				weapon->GetPosition(),
				weapon->GetRadius(),
				p->GetPosition(),
				p->GetRadius(),
				p->GetHeight(),
				outPosition))
			{
				//ダメージを与える
				if (p->ApplyDamage(weapon->GetAttackPower(), 0.5f))
				{
					HitImpact(weapon->GetPosition(), p->GetPosition(), 5.0f, p);
					//弾丸破棄
					weapon->Destroy();
				}
			}
		}
	}
}

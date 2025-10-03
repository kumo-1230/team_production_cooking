#include "EnemyBoss.h"
#include "mathUtils.h"
#include "Player.h"
#include "EnemyManager.h"
#include "EnemySlime.h"
#include "Collision.h"
#include "Enemy.h"
#include <random>


EnemyBoss::EnemyBoss()
{
	model.reset(new Model("Data/Model/Slime/Slime.mdl"));
	em.reset(new EnemyManager());
	//スケーリング
	scale.x = scale.y = scale.z = 0.01f;

	weaponManager.reset(new WeaponManager());

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> Lv(3, 5);

	for (int i = 0; i < 3; i++)
	{
		weaponManager->SetWeaponBild(i, Lv(rd));
	}

	weaponManager->SetWeapon();

	//幅高さ設定
	radius = 0.5f;
	height = 1.0f;

	hitEffect.reset(new Effect("Data/Effect/Hit.efk"));

	//ヒットSE読み込み
	hitSE.reset(Audio::Instance().LoadAudioSource("Data/Sound/Hit.wav"));

	//徘徊ステートへ遷移
	SetEanderState();
}

EnemyBoss::~EnemyBoss()
{
	em->Clear();
}

void EnemyBoss::Update(float elapsedTime, Player* player, const Stage& stage, EnemyManager* enemyManager)
{
	//ステートマイの更新処理
	switch (state)
	{
	case State::Wander:
		UpdatWanderState(elapsedTime, player);
		break;
	case State::Idle:
		UpdatetIdleState(elapsedTime, player);
		break;
	case State::Attack:
		UpdateAttackState(elapsedTime, player);
		break;
	case State::SummonEnemy:
		UpdateSummonEnemyState(elapsedTime, player);
		break;
	case State::Warp:
		UpdateWarpState(elapsedTime, player);
		break;
	}

	//速力処理更新
	UpdateVelocity(elapsedTime, stage);

	//弾丸更新処理
	weaponManager->Update(elapsedTime, *player, *em.get(), *this, LCHAR::ENEMY);

	//プレイヤーと球の衝突処理
	CollisionPlayerVsBullet(player);

	//無敵時間更新
	UpdateInvincidleTimer(elapsedTime);

	//オブジェクト行列更新
	UpdateTransfom();

	em->Update(elapsedTime,player,stage);

	//モデル行列更新
	model->UpdateTransform();
}

void EnemyBoss::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);
	//弾丸描画
	//projectileManager.Render(rc, renderer);
	weaponManager->Render(rc, renderer);

	em->Render(rc, renderer);
}

//デバッグ
void EnemyBoss::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	//基底クラスのデバッグプリミティブ描画
	Enemy::RenderDebugPrimitive(rc, renderer);
	//縄張りのデバッグ
	renderer->RenderCylinder(rc, territoryOrigin, moveTerritory, 1.0f, DirectX::XMFLOAT4(0, 1, 0, 1));
	//縄張りのデバッグ
	renderer->RenderCylinder(rc, territoryOrigin, summonTerritory, 1.0f, DirectX::XMFLOAT4(1, 0, 0, 1));
	//縄張りのデバッグ
	renderer->RenderCylinder(rc, territoryOrigin, warpTerritory, 1.0f, DirectX::XMFLOAT4(0, 0, 1, 1));
	//ターゲット位置をデバッグ
	renderer->RenderSphere(rc, targetPositon, 1.0f, DirectX::XMFLOAT4(1, 1, 0, 1));
	//捜索範囲をデバッグ円柱描画
	//renderer->RenderCylinder(rc, position, searchRange, 1.0f, DirectX::XMFLOAT4(1, 0, 0, 1));
}



//徘徊ステートへ遷移
void EnemyBoss::SetEanderState()
{
	state = State::Wander;

	//目的地点設定
	SetRandomTargetPosition(0.0f, moveTerritory);
}

//待機ステートへ遷移
void EnemyBoss::SetIdleaState()
{
	state = State::Idle;

	//タイマーをランダム設定
	stateTimer = MathUtils::RandomRange(1.0f, 2.0f);
}

void EnemyBoss::SetAttackState(Player* player)
{
	state = State::Attack;
	stateTimer = 0.0f;
	//ランダムな角度
	float theta = MathUtils::RandomRange(-DirectX::XM_PI, DirectX::XM_PI);
	//ランダムな場所
	float range = MathUtils::RandomRange(3.0f, moveTerritory);
	//オリジンからターゲットまでを計算してセットする
	targetPositon.x = player->GetPosition().x + sinf(theta) * range;
	targetPositon.y = player->GetPosition().y;
	targetPositon.z = player->GetPosition().z + cosf(theta) * range;
}

void EnemyBoss::SetSummonEnemy(Player* player)
{
	state = State::SummonEnemy;
	stateTimer = 3.0f;
	if (em->GetEnemyCount() < 4)
	{
		for (int i = 0; i < 2; i++)
		{
			SetRandomTargetPosition(0.0f, summonTerritory);
			SummonPos[i] = targetPositon;
		}
	}
	//ランダムな角度
	float theta = MathUtils::RandomRange(-DirectX::XM_PI, DirectX::XM_PI);
	//ランダムな場所
	float range = MathUtils::RandomRange(3.0f, moveTerritory);
	//オリジンからターゲットまでを計算してセットする
	targetPositon.x = player->GetPosition().x + sinf(theta) * range;
	targetPositon.y = player->GetPosition().y;
	targetPositon.z = player->GetPosition().z + cosf(theta) * range;
}

void EnemyBoss::SetWarpState()
{
	state = State::Warp;

	//ワープまでのタイマーを設定
	stateTimer = 1.0f;
}

//縄張り設定
void EnemyBoss::SetTerritory(const DirectX::XMFLOAT3& origin, float range)
{
	territoryOrigin = origin;
}

void EnemyBoss::SetRandomTargetPosition(float start, float end)
{
	//ランダムな角度
	float theta = MathUtils::RandomRange(-DirectX::XM_PI, DirectX::XM_PI);
	//ランダムな場所
	float range = MathUtils::RandomRange(start, end);
	//オリジンからターゲットまでを計算してセットする
	targetPositon.x = territoryOrigin.x + sinf(theta) * range;
	targetPositon.y = territoryOrigin.y;
	targetPositon.z = territoryOrigin.z + cosf(theta) * range;
}



//プレイヤーが前にいるか
bool EnemyBoss::SearchPlayer(Player* player)
{
	//プレイヤーとの肯定さを考慮して3Dでの距離判定をする
	const DirectX::XMFLOAT3& playerPosition = player->GetPosition();
	float vx = playerPosition.x - position.x;
	float vy = playerPosition.y - position.y;
	float vz = playerPosition.z - position.z;
	float dist = sqrtf(vx * vx + vy * vy + vz * vz);
	if (dist < moveTerritory)
	{
		float distXZ = sqrtf(vx * vx + vz * vz);
		//単位ベクトル化
		vx /= distXZ;
		vz /= distXZ;
		//前方ベクトル
		float frontX = sinf(angle.y);
		float frontZ = cosf(angle.y);
		//二つのベクトルのない席値で前後判定
		float dot = (frontX * vx) + (frontZ * vz);
		if (dot > 0.0f)
		{
			return true;
		}
	}
	return false;
}

bool EnemyBoss::SearchPlayerZone(Player* player, float start, float end)
{
	//プレイヤーとの肯定さを考慮して3Dでの距離判定をする
	const DirectX::XMFLOAT3& playerPosition = player->GetPosition();
	float vx = playerPosition.x - position.x;
	float vy = playerPosition.y - position.y;
	float vz = playerPosition.z - position.z;
	float dist = sqrtf(vx * vx + vy * vy + vz * vz);
	if (dist > start && dist < end)
	{
		return true;
	}
	return false;
}

//目的地へ移動
void EnemyBoss::MoveToTarget(float elapsedTime, float moveSpeedRate, float turnSpeedRate, const DirectX::XMFLOAT3& Pos)
{
	//ターゲット方向への進行ベクトルを算出
	float vx = Pos.x - position.x;
	float vz = Pos.z - position.z;
	float dist = sqrtf(vx * vx + vz * vz);
	//正規化
	vx /= dist;
	vz /= dist;
	//移動処理
	Move(elapsedTime, vx, vz, moveSpeed * moveSpeedRate);
	Turn(elapsedTime, vx, vz, turnSpeed * turnSpeedRate);
}

//召喚したエネミーと弾の当たり判定
void EnemyBoss::CollisionSummonEnemyVsBullet(Weapon* w, Effect* hitEffect, AudioSource* hitSE)
{
	for (int i = 0; i < em->GetEnemyCount(); i++)
	{
		Enemy* e = em->GetEnemy(i);
		//衝突処理
		DirectX::XMFLOAT3 outPosition;
		if (Collision::IntersectSphereVsCylinder(
			w->GetPosition(),
			w->GetRadius(),
			e->GetPosition(),
			e->GetRadius(),
			e->GetHeight(),
			outPosition))
		{
			//ダメージを与える
			if (e->ApplyDamage(w->GetAttackPower(), 0.5f, em.get()))
			{
				HitImpact(w->GetPosition(), e->GetPosition(), 5.0f, e);
				//弾丸破棄
				w->Destroy();
			}
		}
	}
}

//召喚弾とプレイヤーの当たり判定
void EnemyBoss::CollisionPlayerVsBullet(Player* p)
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

//徘徊ステート更新処理
void EnemyBoss::UpdatWanderState(float elapsedTime, Player* player)
{
	//目的地までXZ平面での移動判定
	float vx = targetPositon.x - position.x;
	float vz = targetPositon.z - position.z;
	float distSq = vx * vx + vz * vz;
	if (distSq < radius * radius)
	{
		//次の目的地点設定
		territoryOrigin = position;
		SetIdleaState();
	}

	//目的地点へ移動
	MoveToTarget(elapsedTime, 1.0f, 1.0f,targetPositon);

	//プレイヤー捜索
	if (SearchPlayer(player))
	{
		//見つけたら攻撃ステートへ
		SetAttackState(player);
	}
	//ワープゾーンにプレイヤーがいるか
	if (SearchPlayerZone(player,summonTerritory,warpTerritory))
	{
		//見つけたらワープ
		SetWarpState();
	}
	//召喚ゾーンにいるか
	if (SearchPlayerZone(player, moveTerritory, summonTerritory))
	{
		SetSummonEnemy(player);
	}
}

//待機ステート更新
void EnemyBoss::UpdatetIdleState(float elaspedTime, Player* player)
{
	//タイマー処理
	stateTimer -= elaspedTime;
	if (stateTimer < 0.0f)
	{
		//徘徊ステートへ遷移
		SetEanderState();
	}

	//プレイヤー捜索
	if (SearchPlayer(player))
	{
		//見つけたら攻撃ステートへ
		SetAttackState(player);
	}
}

//追跡ステート更新処理
void EnemyBoss::UpdateAttackState(float elapsedTime, Player* player)
{
	//目的地までXZ平面での移動判定
	float vx = targetPositon.x - position.x;
	float vz = targetPositon.z - position.z;
	float distSq = vx * vx + vz * vz;
	if (distSq < radius * radius)
	{
		SetRandomTargetPosition(0.0f, moveTerritory);
		stateTimer = 0.5f;
	}

	//目的地へ移動
	MoveToTarget(elapsedTime, 0.0f, 1.0f,player->GetPosition());
	MoveToTarget(elapsedTime, 1.0f, 0.0f,targetPositon);

	//ワープゾーンにプレイヤーがいるか
	if (SearchPlayerZone(player, summonTerritory, warpTerritory))
	{
		//見つけたらワープ
		SetWarpState();
	}
	//召喚ゾーンにいるか
	if (SearchPlayerZone(player, moveTerritory, summonTerritory))
	{
		SetSummonEnemy(player);
	}

	//タイマー処理
	stateTimer -= elapsedTime;
	if (stateTimer < 0.0f)
	{
		//前方向
		DirectX::XMFLOAT3 dir;
		dir.x = sinf(angle.y);
		dir.y = 0.0f;
		dir.z = cosf(angle.y);
		//発射位置
		DirectX::XMFLOAT3 pos;
		pos.x = position.x;
		pos.y = position.y + height * 0.5f;
		pos.z = position.z;
		//発射
		weaponManager->GetWeapon(WEAPON::BULLET_STRAIGHT)->SetCoolTime();
		stateTimer = 2.0f;

		if (!SearchPlayer(player))
		{
			//待機ステートへ遷移
			SetIdleaState();
		}
	}
}

void EnemyBoss::UpdateSummonEnemyState(float elapsedTime, Player* player)
{
	stateTimer -= 1 * elapsedTime;

	//目的地点へ移動
	MoveToTarget(elapsedTime, 1.0f, 1.0f,targetPositon);
	//目的地までXZ平面での移動判定
	float vx = targetPositon.x - position.x;
	float vz = targetPositon.z - position.z;
	float distSq = vx * vx + vz * vz;
	if (distSq < radius * radius)
	{
		stateTimer = 0.0f;
	}
	if (Collision::IntersectSphereVsCylinder(
		targetPositon, 1.0f,
		position, radius, height))
	{
		//次の目的地点設定
		territoryOrigin = position;
	}
	territoryOrigin = position;
	if (stateTimer <= 0.0f)
	{
		EnemySlime* enemy;
		for (int i = 0; i < 2; i++)
		{
			if (em->GetEnemyCount() < 4)
			{
				enemy = new EnemySlime();
				enemy->SetPosition({ SummonPos[i].x,0,SummonPos[i].y });
				em->Register(enemy);
			}
		}
		SetEanderState();
	}
}

void EnemyBoss::UpdateWarpState(float elapsedTime, Player* player)
{
	stateTimer -= 1 * elapsedTime;

	if (stateTimer < 0.0f)
	{
		//ワープゾーン範囲にランダムにワープ
		//ランダムな角度
		float theta = MathUtils::RandomRange(-DirectX::XM_PI, DirectX::XM_PI);
		//ランダムな場所
		float range = MathUtils::RandomRange(3.0f, moveTerritory);
		//オリジンからターゲットまでを計算してセットする
		targetPositon.x = player->GetPosition().x + sinf(theta) * range;
		targetPositon.y = player->GetPosition().y;
		targetPositon.z = player->GetPosition().z + cosf(theta) * range;
		//ワープ
		position = targetPositon;

		territoryOrigin = position;
		SetEanderState();

	}

	if (!SearchPlayerZone(player, summonTerritory, warpTerritory))
	{
		SetEanderState();
	}
}

//死亡した時に呼ばれる
void EnemyBoss::OnDead(EnemyManager* enemyManager)
{
	//自身を削除
	//delete this;
	Destroy(enemyManager);
}

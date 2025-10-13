#include "Player.h"
#include "System/Input.h"
#include <imgui.h>
#include "Collision.h"
#include "EffectManager.h"
#include "System/Audio.h"
#include "stage.h"
#include "RayCast.h"
#include <random>
#include "BulletRotate.h"
#include "ParentChild.h"
#include "KeyInput.h"
#include "BaconBox.h"
#include "omurice.h"

#define DEBUG

Player::Player()
{
	hitEffect = new Effect("Data/Effect/Hit.efk");

	//ヒットSE読み込み
	hitSE = Audio::Instance().LoadAudioSource("Data/Sound/Hit.wav");

	Initialize();
}

Player::~Player()
{
	delete hitSE;

	delete hitEffect;
}

void Player::Initialize()
{
	model = std::make_unique<Model>("Data/Model/kyara.mdl");

	//モデルが大きいからスケーリング
	scale.x = scale.y = scale.z = 0.1f;

	HP = 10;
}

void Player::Finalize()
{
}

//更新処理
void Player::Update(float elapsdTime, const Camera* camera, const StageManager* stage,FoodManager* foodMnager,DishManager* dishManager)
{
	InputMove(elapsdTime,camera);

	//ジャンプ入力処理
	InputJump();

	//速力更新処理
	UpdateVelocity(elapsdTime,stage->GetFloor());

	////プレイヤーと敵の衝突処理
	//CollisionPlayerVsEnemies(enemyManager);

	
	DirectX::XMFLOAT3 childrenByeByePos = { 0,5.0f,15.0f};

	KeyInput k;

	if (k.GetKeyDown('E'))
	{
		takeItem(foodMnager,dishManager);
	}

	if (k.GetKeyDown('Q'))
	{
		DropItem(foodMnager,dishManager, stage);
	}

	if (haveIng)
	{
		ParentChild::MakeParentAndChild(transform, haveIng->getPosition(), haveIng->getScale(), haveIng->getAngle(), haveIng->getTransform(), childrenByeByePos);
		haveIng->setScale({ 1,1,1 });
	}
	if (haveDish)
	{
		ParentChild::MakeParentAndChild(transform, haveDish->getPosition(), haveDish->getScale(), haveDish->getAngle(), haveDish->getTransform(), childrenByeByePos);
		haveDish->setScale({ 0.1f,0.1f,0.1f });
	}



		
	//DirectX::XMFLOAT3 outPos;
	//if (Collision::IntersectBoxVsCylinder(stage->GetBoxPosition(0), stage->GetBoxLength(0), position, radius, height, outPos))
	//{
	//	position = outPos;
	//}
	//if (Collision::IntersectBoxVsCylinder(stage->GetBoxPosition(0), stage->GetBoxLength(0), position, radius, height, outPos))
	//{
	//	position = outPos;
	//}

	//無敵時間更新
	UpdateInvincidleTimer(elapsdTime);

	//オブジェクト行列更新
	UpdateTransfom();

	//モデル行列更新
	model->UpdateTransform();

	//エフェクト更新処理
	EffectManager::Instance().Update(elapsdTime);
}

//描画処理
void Player::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);

	//エフェクト更新処理
	EffectManager::Instance().Render(rc.view, rc.projection);
}

//デバッグ用GUI描画
void Player::DrawDebugGUI()
{
#ifdef DEBUG
	//なんかのポジションを取ってくる
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	//表示場所
	ImGui::SetNextWindowPos(ImVec2(pos.x + 10, pos.y + 10), ImGuiCond_Once);
	//大きさ
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Player", nullptr, ImGuiWindowFlags_None))
	{
		//トランスフォーム
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//位置
			ImGui::InputFloat3("Position", &position.x);

			//回転
			DirectX::XMFLOAT3 a;

			a.x = DirectX::XMConvertToDegrees(angle.x);
			a.y = DirectX::XMConvertToDegrees(angle.y);
			a.z = DirectX::XMConvertToDegrees(angle.z);
			ImGui::InputFloat3("Angle", &a.x);
			angle.x = DirectX::XMConvertToRadians(a.x);
			angle.y = DirectX::XMConvertToRadians(a.y);
			angle.z = DirectX::XMConvertToRadians(a.z);

			//スケール
		}
	}
	ImGui::End();

#endif // DEBUG
}

void Player::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{

	//基底クラスの関数呼び出し
	Character::RenderDebugPrimitive(rc, renderer);

	//弾丸デバッグプリミティブ描画
	//projectileManager.RenderDebugPrimitive(rc, renderer);
}

void Player::OnLanding()
{
	jumpCount = 0;
}

void Player::InputMove(float elapsedTime, const Camera* camera)
{
	//進行ベクトル取得
	DirectX::XMFLOAT3 moveVec = GetMoveVec(*camera);

	//移動処理
	Move(elapsedTime, moveVec.x, moveVec.z, moveSpeed);

	//旋回処理
	Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);

}

DirectX::XMFLOAT3 Player::GetMoveVec(const Camera& camera) const
{
	//入力情報を取得
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax         = gamePad.GetAxisLX();
	float ay         = gamePad.GetAxisLY();

	//カメラ方向とスティック入力値にヨット進行方向を計算する
	const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
	const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

	//移動ベクトルはXZ平面に水平なベクトルになるようにする
	//カメラ右方向ベクトルをXZ単位ベクトルに変換
	float cameraRightX      = cameraRight.x;
	float cameraRightZ      = cameraRight.z;
	float cameraRightLength = sqrtf(cameraRightX * cameraRight.x + cameraRightZ * cameraRight.z);
	if (cameraRightLength > 0.0f)
	{
		//単位ベクトル化
		cameraRightX /= cameraRightLength;
		cameraRightZ /= cameraRightLength;
	}

	//カメラ前方向ベクトルをXZ単位ベクトルに変換
	float cameraFrontX      = cameraFront.x;
	float cameraFrontZ      = cameraFront.z;
	float cameraFrontLength = sqrtf(cameraFrontX * cameraFront.x + cameraFrontZ * cameraFront.z);
	if (cameraFrontLength > 0.0f)
	{
		//単位ベクトル化
		cameraFrontX /= cameraFrontLength;
		cameraFrontZ /= cameraFrontLength;
	}

	//スティックの水平入力値をカメラ右方向に反映し、
	//スティックの垂直入力値をカメラ前方向に反映し、
	//進行ベクトルを計算する
	DirectX::XMFLOAT3 vec;
	vec.x = cameraRightX * ax + cameraFrontX * ay;
	vec.z = cameraRightZ * ax + cameraFrontZ * ay;

	//Y軸方向には移動しない
	vec.y = 0.0f;

	return vec;
}

//＠入れ追うアート
//プレイヤーとエネミーの衝突処理
void Player::CollisionPlayerVsEnemies(EnemyManager* enemyManager)
{
	////EnemyManager& enemyManager = EnemyManager::Instance();
	////すべての敵と総当たりで衝突処理
	//int enemyConst = enemyManager->GetEnemyCount();

	//for (int i = 0; i < enemyConst; i++)
	//{
	//	Enemy* enemy = enemyManager->GetEnemy(i);

	//	//衝突処理
	//	DirectX::XMFLOAT3 outPositon;
	//	if (Collision::IntersectCylinderVsCylinder(
	//		position, radius, height,
	//		enemy->GetPosition(), enemy->GetRadius(), enemy->GetHeight(),
	//		outPositon))
	//	{
	//		//if (enemy->GetPosition().y + enemy->GetHeight() - position.y < 0.1)
	//		if (position.y > enemy->GetPosition().y + enemy->GetHeight() - 0.1)
	//		{
	//			jumpCount = 1;
	//			//position.y = enemy->GetPosition().y + enemy->GetHeight();
	//			Jump(jumpSpeed * 0.5f);
	//			break;
	//		}
	//		enemy->SetPosition(outPositon);
	//	}
	//}
}

void Player::InputJump()
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	if (gamePad.GetButtonDown() & GamePad::BTN_A)
	{
		if (jumpCount < jumpLimit)
		{
			jumpCount++;
			Jump(jumpSpeed);
		}
	}
}


void Player::InputProjectile(EnemyManager* enemyManager)
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	{
		//if (gamePad.GetButtonDown() & GamePad::BTN_Y)
		//{
		//	//発射
		//	BulletRotate* pr = new BulletRotate(&projectileManager);
		//	pr->Launch({position.x,position.y + height * 0.5f,position.z }, pos, offset);
		//}

		//if (gamePad.GetButtonDown() & GamePad::BTN_X)
		//{
		//	std::random_device rd;
		//	std::mt19937 mt(rd());
		//	std::uniform_int_distribution<> distXZ(-3.0f,3.0f);
		//	std::uniform_int_distribution<> distY(0.5f,3.0f);
		//	//前方向
		//	DirectX::XMFLOAT3 dir;
		//	dir.x = sinf(angle.y);
		//	dir.y = 0;
		//	dir.z = cosf(angle.y);
		//	//発射位置(腰当たり)
		//	DirectX::XMFLOAT3 pos;
		//	pos.x = position.x + distXZ(mt);
		//	pos.y = position.y + height * 0.5f + distY(mt);
		//	pos.z = position.z + distXZ(mt);
		//	//ターゲット
		//	DirectX::XMFLOAT3 target;
		//	target.x = sinf(angle.y);
		//	target.y = 0;
		//	target.z = cosf(angle.y);
		//	//一番近くの敵をターゲットにする
		//	float dist = FLT_MAX;
		//	//EnemyManager& enemyManager = EnemyManager::Instance();
		//	int enemyCount = enemyManager->GetEnemyCount();
		//	for (int i = 0; i < enemyCount; i++)
		//	{
		//		//XZ平面での範囲チェック
		//		float vx = enemyManager->GetEnemy(i)->GetPosition().x - position.x;
		//		float vy = enemyManager->GetEnemy(i)->GetPosition().y - position.y;
		//		float vz = enemyManager->GetEnemy(i)->GetPosition().z - position.z;
		//		float range = sqrtf(vx * vx + vy * vy + vz * vz);
		//		if (range < dist)
		//		{
		//			dist = range;
		//			target.x = enemyManager->GetEnemy(i)->GetPosition().x;
		//			target.y = enemyManager->GetEnemy(i)->GetPosition().y + enemyManager->GetEnemy(i)->GetHeight() * 0.5f;
		//			target.z = enemyManager->GetEnemy(i)->GetPosition().z;
		//		}
		//	}
		//	//発射
		//	ProjectileHoming* pr = new ProjectileHoming(&projectileManager);
		//	pr->Launch(dir, pos, target);
		//	//projectileManager.Register(pr);
		//}
	}
}

void Player::UpdateHorizontalMove(float elapsedTime, const Stage* stage)
{
	using namespace DirectX;

	XMFLOAT3 s = {
		position.x,
		position.y + height * 0.5f,
		position.z,
	};
	XMFLOAT3 e = {
		position.x + velocity.x * elapsedTime,
		position.y + height * 0.3f,
		position.z + velocity.z * elapsedTime,
	};

	if (velocity.x > 0.001f)
	{
		int a = 0;
	}

	XMFLOAT3 p, n;

	//if (Hit::RayCast(s, e, stage->GetTransform(), &stage->GetModel(), p, n))
	//{
	//	//交点から終点へのベクトルを求める
	//	DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&p);
	//	DirectX::XMVECTOR E = DirectX::XMLoadFloat3(&e);
	//	DirectX::XMVECTOR PE = DirectX::XMVectorSubtract(E, P);

	//	//三角関数で終点から壁までの長さを求める
	//	DirectX::XMVECTOR N = DirectX::XMLoadFloat3(&n);
	//	DirectX::XMVECTOR A = DirectX::XMVector3Dot(-PE, N);
	//	//壁までの長さを少しだけ長くなるように補正する
	//	float a = fabsf(DirectX::XMVectorGetX(A)) + 0.001f;

	//	//壁ずりベクトルを求める
	//	DirectX::XMVECTOR R = DirectX::XMVectorAdd(PE, DirectX::XMVectorScale(N, a));

	//	//壁ずりあとの位置を求める
	//	DirectX::XMVECTOR Q = DirectX::XMVectorAdd(P, R);
	//	DirectX::XMFLOAT3 q;
	//	DirectX::XMStoreFloat3(&q, Q);

	//	//壁際で壁ずり後の位置がめり込んでいないか例キャストでチェックする
	//	if (Hit::RayCast(s, q, stage->GetTransform(), &stage->GetModel(), p, n))
	//	{
	//		//めり込んでいた場合はプレイヤーの位置に今回の例キャストした交点を設定する
	//		//プレイヤーの位置が壁にぴったりくっつかないように補正する
	//		P = DirectX::XMLoadFloat3(&p);
	//		DirectX::XMVECTOR S = DirectX::XMLoadFloat3(&s);
	//		DirectX::XMVECTOR PS = DirectX::XMVectorSubtract(S, P);
	//		DirectX::XMVECTOR V = XMVector3Normalize(PS);
	//		P = XMVectorAdd(P, XMVectorScale(V, 0.001f));
	//		DirectX::XMStoreFloat3(&p, P);
	//		position.x = p.x;
	//		position.z = p.z;
	//	}
	//	else
	//	{
	//		position.x = q.x;
	//		position.z = q.z;
	//	}

	//}
	{
		Character::UpdateHorizontalMove(elapsedTime, stage);
	}
}

void Player::UpdateVerticalMove(float elapsedTime, const Stage* stage)
{
	float MoveY = velocity.y * elapsedTime;

	bool IsGround = isGround;
	isGround = IsGround;

	//落下中に設置処理をする
	if (velocity.y < 0.0f)
	{

		DirectX::XMFLOAT3 S = { position.x, position.y + height * 0.5f, position.z };
		DirectX::XMFLOAT3 E = { position.x, position.y + gravity * elapsedTime , position.z };

		float DownHillOffset = downhillOffset * elapsedTime;

		if (IsGround)
		{
			E.y -= DownHillOffset;
			isGround = false;
		}
		DirectX::XMFLOAT3 hitPos, hitNormal;
		if (Hit::RayCast(S, E, stage->GetTransform(), &stage->GetModel(), hitPos, hitNormal))
		{
			//交点のY座標をプレイヤーの位置にする
			position.y = hitPos.y;
			velocity.y = 0.0f;
			MoveY = velocity.y * elapsedTime;
			isGround = true;
			OnLanding();
		}
	}

	position.y += MoveY;

	position.y = 0.0f;

}

void Player::Cocking(float elapsedTime, const StageManager* stageManager)
{
	//すべてのマップチップを判定して一番近い料理できるものを調べる
	//for (int i = 0;i < stageManager.GetTileMapLength();i++)
	//{
	//	stageManager
	//}
}

bool Player::ApplyDamage(float dmage, float invincidleTime)
{
	//ダメージが0の場合は健康状態を変更する必要がない
	if (dmage == 0) return false;

	//死亡している場合は健康状態を変更しない
	if (HP <= 0) return false;

	if (invincidleTimer > 0) return false;

	invincidleTimer = invincidleTime;

	//ダメージ処理
	HP -= dmage;

	//健康状態を変更した場合はtrueを返す
	return true;
}

void Player::takeItem(FoodManager* foodmanager,DishManager* dishManager)
{
	float nearItem;
	//float nearBox;
	float nearDish;
	{
		//一番近い皿か物を判別して手に持つ
		DirectX::XMFLOAT3 itemPos;
		DirectX::XMFLOAT3 dishPos;
		Ingredients* nearestItem = nullptr;
		Dish* nearestDish = nullptr;
		float ingDis = FLT_MAX;
		float dishDis = FLT_MAX;
		for (int i = 0; i < foodmanager->GetFoodCount(); i++)
		{
			Ingredients* item = foodmanager->GetFood(i);
			if (item == haveIng)
			{
				continue;
			}

			itemPos = item->getPosition();

			float vx = itemPos.x - position.x;
			float vz = itemPos.z - position.z;
			float Length = sqrtf(vx * vx + vz * vz);

			float distance = radius + foodmanager->GetFood(i)->getRadius();

			if (distance > Length&&Length <ingDis)
			{
				ingDis = Length;
				nearestItem = item;
			}
		}
		for (int j = 0; j < dishManager->getDishNum();j++)
		{
		
			Dish* dish = dishManager->getDish(j);
			dishPos = dish->getPosition();

			if (dish == haveDish)
			{
				continue;
			}


			float vx = dishPos.x - position.x;
			float vz = dishPos.z - position.z;
			float Length = sqrtf(vx * vx + vz * vz);

			float distance = radius + dishManager->getDish(j)->getRadius();

			if (distance > Length && Length < dishDis)
			{
				dishDis = Length;
				nearestDish = dish;
			}
		}

		if (haveIng != nullptr && haveDish != nullptr)
		{
			haveDish->setOndishFood(nearestItem);
			haveIng = haveDish->MixDishOnFood(haveIng, foodmanager);
			return;
		}
		
		if (nearestDish != nullptr && (dishDis <= ingDis || nearestItem == nullptr))
		{
			haveDish = nearestDish;
		}
		else if (nearestItem != nullptr)
		{
			haveIng = nearestItem;
		}

	}
}

void Player::DropItem(const FoodManager* foodManager,const DishManager* dishManager,const StageManager* stagemanager)
{

	DirectX::XMFLOAT3 dropPos = position;
	dropPos.y = 0;
	//プレイヤーの足元に置く
	if (haveIng)
	{
		haveIng->setPosition(dropPos);
		haveIng->setScale({ 0.1f,0.1f,0.1f });

		haveIng->UpdateTransfom();
		haveIng = nullptr;
	}

	if (haveDish)
	{
		

		haveDish->setPosition(dropPos);
		haveDish->setScale({ 0.01f,0.01f,0.01f });

		haveDish->UpdateTransfom();
		//haveIng->model->UpdateTransform();

		haveDish = nullptr;
	}
}

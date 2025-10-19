#pragma once

#include "System/ModelRenderer.h"
#include "Character.h"
#include "Effect.h"
#include "System/AudioSource.h"
#include "Camera.h"
#include <memory>
#include "StageManager.h"
#include "food.h"
#include "foodManager.h"
#include "Dish.h"
#include "DishManager.h"

//プレイヤー
class Player : public Character
{
private:
	std::unique_ptr<Model> model = nullptr;
	float moveSpeed = 10.0f;

	float turnSpeed = DirectX::XMConvertToRadians(720);

	float jumpSpeed = 12.0f;

	int jumpCount = 0;
	int jumpLimit = 2;

	int money = 0;

	KeyInput k;

	Ingredients* haveIng;
	Dish*        haveDish;

	DirectX::XMFLOAT3 p, l;

	std::unique_ptr<Effect> hitEffect = nullptr;

	AudioSource* hitSE = nullptr;
	
public:
	int orderSlot[4];
	float orderTimer[4];

	//合計点数と合計金額の格納
	struct  omu_Result
	{
		int count = 0;
		int charge = 0;
		std::unique_ptr<Sprite> omuSprite = nullptr;
		std::unique_ptr<Sprite> omuNumber = std::make_unique<Sprite>("Data/Sprite/Number.png");
	};

	omu_Result omu[3];
public:
	Player();
	~Player() override;

	//初期化
	void Initialize();

	//終了化
	void Finalize();

private:
	void HitStage(const StageManager* stage);

public:
	void SetFood(Ingredients* f)
	{
		haveIng = f;
		//if (f == nullptr)
		//{
		//	haveIng = nullptr; // 手放す
		//}
		//else if (!haveIng)
		//{
		//	haveIng = f;
		//}
	}
	void SetDish(Dish* dish)
	{
		if (dish == nullptr)
		{
			haveDish = nullptr;
		}
		else if (!haveDish)
		{
			haveDish = dish;
		}
	}

	const Dish* GetHaveDish() const { return haveDish; }

public:
	//更新処理
	void Update(float elapsedTime,const Camera* camera, const StageManager* stage,FoodManager* foodManager,DishManager* dishManager);

	//描画処理
	void Render(const RenderContext& rc, ModelRenderer* render);

	//デバッグ用GUI描画
	void DrawDebugGUI();

	//デバッグプリミティブ描画
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	bool ApplyDamage(float dmage, float invincidleTime)override;

	void setScore(int moneys) { money += moneys; }
	void SetMoney(int moneys) { money = moneys; }
	int getScore() { return money; }
	Ingredients* getIng() { return haveIng; }
	Dish* getDish() { return haveDish; }


	

protected:
	//着地したときに呼ばれる
	void OnLanding() override;

private:
	//スティック入力値から移動ベクトルを取得
	DirectX::XMFLOAT3 GetMoveVec(const Camera& camera) const;

private:

	//移動入力処理
	void InputMove(float elapsedTime, const Camera* camera);
	//ジャンプ入力処理
	void InputJump();

	void UpdateHorizontalMove(float elapsedTime, const Stage* stage) override;

	void UpdateVerticalMove(float elapsedTime, const Stage* stage) override;

	//料理処理
	void Cocking(float elapsedTime,const StageManager* stagemanager);

	//弾丸入力処理
	void InputProjectile(EnemyManager* enemyManager);

	//プレイヤーとエネミーとの衝突処理
	void CollisionPlayerVsEnemies(EnemyManager* enemyManager);

	void UseItem(FoodManager* foodmanager,DishManager* dishManager);

	void DropItem(const FoodManager* foodManager,const DishManager* dishManager, const StageManager* stagemanager);
};
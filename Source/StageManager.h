#pragma once
#include "stage.h"
#include "Stove.h"
#include "KeyInput.h"
#include "Utensils.h"
#include "System/Sprite.h"
#include "foodManager.h"

class Player;


class StageManager
{
public:
	enum TILE_MODEL
	{
		NONE = 0,
		BACON,      //ベーコン
		CABBAGE,    //キャベツ
		EGG,        //卵
		OFFER,      //提供
		RETURN_DISH,//皿が返ってくるとこ
		ONION,      //玉ねぎ
		POTATO,     //ポテト
		RICE,       //米
		TOMATO,     //トマト

		            //設置可能
		BOARD,      //まな板
		POT,        //鍋
		SINK,       //シンク
		STOVE,      //ストーブ
		TABLE,      //テーブル
		BOX,        //食材ボックス

		            //ソース
		KETCHUP,    //ケチャップ
		DEMI,       //デミグラス
		WHITE,      //ホワイトソース
		PLAYER,		//スホーン位置
	};
private:
	//床
	std::unique_ptr<Stage> floor;//床
	//タイルマップ
	std::vector<std::unique_ptr<Stage>> tileMapBox;//食材ボックス
	std::vector<std::unique_ptr<Utensils>> tileMapUtensils;//調理器具
	std::unique_ptr<Stage> cursor;//置く場所
	std::unique_ptr<KeyInput> key;//インプット
	std::vector<std::vector<std::unique_ptr<Utensils>>> TileMapBank;//マップ構築中の保存場所
	int x = 0,//今のX
		y = 0,//今のY
		TileMode = 0,//今のモード
		Lv = 0;//今のレベル
	int range;
	bool Long = false;
	int nextX = 0,//ニマスの時の隣のX
		nextY = 0;//ニマスの時の隣のY
	int oldX = -1,//一個前のX
		oldY = -1,//一個前のY
		oldTileMode = -1,//一個前のモード
		oldLv = -1;//一個前のレベル
	bool build = true;//ビルドが終わったか
	int subtractionMoney = 0;//最終的に引かれるお金

	const int ADD_MONEY[3] = { 3000,4000,5000 };

	std::unique_ptr<Sprite> sprite;
	std::unique_ptr<Sprite> spriteWarning;

	//プレイヤーがスポーンする場所のインデックスを保存
	int PlayerPos{-1};

	int timerCount{0};

	bool A = true;//不透明度



	std::unique_ptr<Sprite> spritePlus;
	std::unique_ptr<Sprite> spriteNo;
	std::unique_ptr<Sprite> spriteMinus;
	std::unique_ptr<Sprite> spriteMiss;

	float renderPosX;
	float renderPosY;

	float timer;

	bool TipRenderPlus;
	bool TipRenderNo;
	bool TipRenderMiss;
	bool TipRenderMinus;

public:
	StageManager();
	~StageManager();

	void Initialize();
public:
	////////////////////////////////////////////

	//床ゲット
	const Stage* GetFloor() const { return floor.get(); }
	//食材Boxゲット
	const Stage* GetTileMapBox(int i) const { return tileMapBox[i].get(); }
	//何個あるか
	const int GetTileMapBoxLength() const { return tileMapBox.size();}
	//場所
	const DirectX::XMFLOAT3& GetBoxPosition(int i) const { return tileMapBox[i]->GetPosition(); }
	//長さ
	const DirectX::XMFLOAT3& GetBoxLength(int i) const { return tileMapBox[i]->GetLength(); }

	//調理器具
	const Utensils* GetTileMapUtensils(int i) const { return tileMapUtensils[i].get(); }
	//調理器具の量
	const int GetTileMapUtensilsLength() const { return tileMapUtensils.size();}
	//場所
	const DirectX::XMFLOAT3& GetUtensilsPosition(int i) const { return tileMapUtensils[i]->GetPosition(); }
	//長さ
	const DirectX::XMFLOAT3& GetUtensilsLength(int i) const { return tileMapUtensils[i]->GetLength(); }

	//タイルマップにセットする
	void SetMapTip();
	//引く分のお金
	const int GetMoney() const { return subtractionMoney; }

	void SetBuild(bool b) {
		build = b;
	}

	////////////////////////////////////////////

public:

	void Update(float elapsedTime, DishManager* DM, Player* P,FoodManager* F);
	void Render(const RenderContext& rc, ModelRenderer* renderer);
	void Render2D(const RenderContext& rc);
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	void BuildingMap();

};
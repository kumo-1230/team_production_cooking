#pragma once
#include "stage.h"
#include "Stove.h"
#include "KeyInput.h"
#include "Utensils.h"

enum TILE_MODEL
{
	NONE = 0,
	BACON,  //ベーコン
	CABBAGE,//キャベツ
	EGG,    //卵
	OFFER,  //提供
	ONION,  //玉ねぎ
	POTATO, //ポテト
	RICE,   //米
	TOMATO, //トマト

	//設置可能
	FLYER,  //フライヤー
	POT,    //鍋
	SINK,   //シンク
	STOVE,  //ストーブ
	TABLE,  //テーブル
};

class StageManager
{
private:
	//床
	std::unique_ptr<Stage> floor;
	//タイルマップ
	std::vector<std::unique_ptr<Stage>> tileMapBox;
	std::vector<std::unique_ptr<Utensils>> tileMapUtensils;
	std::vector<std::vector<std::unique_ptr<Stage>>> mapStage;
	std::unique_ptr<Stage> cursor;
	std::unique_ptr<KeyInput> key;
	std::vector<std::vector<std::unique_ptr<Stage>>> TileMapBank;
	int x = 0, y = 0,TileMode = 0,Lv = 0;
	int oldX = -1, oldY = -1,oldTileMode = -1,oldLv = -1;
	bool build = true;
	int count = 0;

public:
	StageManager();
	~StageManager();

	void Initialize();
public:
	////////////////////////////////////////////

	const Stage* GetFloor() const { return floor.get(); }
	//指定した要素数のタイルマップを取得
	const Stage* GetTileMapBox(int i) const { return tileMapBox[i].get(); }

	const int GetTileMapBoxLength() const { return tileMapBox.size();}

	const DirectX::XMFLOAT3& GetBoxPosition(int i) const { return tileMapBox[i]->GetPosition(); }

	const DirectX::XMFLOAT3& GetBoxLength(int i) const { return tileMapBox[i]->GetLength(); }


	const Utensils* GetTileMapUtensils(int i) const { return tileMapUtensils[i].get(); }

	const int GetTileMapUtensilsLength() const { return tileMapUtensils.size();}

	const DirectX::XMFLOAT3& GetUtensilsPosition(int i) const { return tileMapUtensils[i]->GetPosition(); }

	const DirectX::XMFLOAT3& GetUtensilsLength(int i) const { return tileMapUtensils[i]->GetLength(); }

	//タイルマップにセットする
	void SetMapTip();

	////////////////////////////////////////////

public:

	void Update(float elapsedTime);
	void Render(const RenderContext& rc, ModelRenderer* renderer);
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	void BuildingMap();

};
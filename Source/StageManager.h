#pragma once
#include "stage.h"
#include "Stove.h"
#include "KeyInput.h"

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
	std::vector<std::unique_ptr<Stage>> tileMap;
	std::vector<std::vector<std::unique_ptr<Stage>>> mapStage;
	std::unique_ptr<Stage> cursor;
	std::unique_ptr<KeyInput> key;
	std::vector<std::vector<std::unique_ptr<Stage>>> TileMapBank;
	int x = 0, y = 0,TileMode = 0,Lv = 0;
	int oldX = -1, oldY = -1,oldTileMode = -1,oldLv = -1;
	bool build = true;

public:
	StageManager();
	~StageManager();

	void Initialize();
public:
	////////////////////////////////////////////

	const Stage* GetFloor() const { return floor.get(); }
	//指定した要素数のタイルマップを取得
	const Stage* GetTileMap(int i) const { return tileMap[i].get(); }

	const int GetTileMapLength() const { return tileMap.size();}

	const DirectX::XMFLOAT3& GetPosition(int i) const { return tileMap[i]->GetPosition(); }

	const DirectX::XMFLOAT3& GetLength(int i) const { return tileMap[i]->GetLength(); }

	//タイルマップにセットする
	void SetMapTip();

	////////////////////////////////////////////

public:

	void Update(float elapsedTime);
	void Render(const RenderContext& rc, ModelRenderer* renderer);
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	void BuildingMap();

};
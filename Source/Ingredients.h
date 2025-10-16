#pragma once

#include "System//Graphics.h"
#include "System/Model.h"
#include <memory>

enum foodType
{
	RICE = 0,
	ONION,
	EGG,
	TOMATO,
	CHICKENRICE,
	OMURICE,
};


class Ingredients
{
protected:
	std::unique_ptr<Model> model;
	DirectX::XMFLOAT3	position = { 0,0,0 };
	DirectX::XMFLOAT3	angle = { 0,0,0 };
	DirectX::XMFLOAT3	scale = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = {
		//スケールx
		1, 0, 0, 0,
		//スケールy
		0, 1, 0, 0,
		//回転
		0, 0, 1, 0,
		//位置
		0, 0, 0, 1
	};


	//半径
	float radius = 0.5f;

	//高さ玉ねぎ
	float height = 2.0f;

	bool IsUtensils;
	int myFoodType;
	int nowLV = 0;

	int omuType = -1;
public:
	Ingredients();
	virtual ~Ingredients();
	virtual void Update() {};
	//初期化
	void Initialize();

	//終了化
	void Finalize();


	////////////////////////////////
	virtual void setPosition(const DirectX::XMFLOAT3 pos);
	virtual void setScale(const DirectX::XMFLOAT3 scale);
	virtual const DirectX::XMFLOAT3&  getPosition() { return position; }
	const float  getRadius() { return radius; }
	DirectX::XMFLOAT4X4& getTransform()  { return transform; }
	const DirectX::XMFLOAT3&  getScale() { return scale; }
	const DirectX::XMFLOAT3&  getAngle() { return angle; }
	////////////////////////////////

	////////////////////////////////
	int GetLevel() { return nowLV; }
	void SetLevel(int i) { nowLV = i; }

	int GetType() { return myFoodType; }
	int GetOmuType() { return omuType; }
	void SetType(int i) { myFoodType = i; }
	////////////////////////////////
	const int GetLv() { return nowLV; }
	void SetLv(int l) { nowLV = l; }
	void SetUtensils(bool b) { IsUtensils = b; }

private:
public:

	//描画処理
	virtual	void Render(const RenderContext& rc, ModelRenderer* render) = 0;

	//デバッグ用GUI描画
	void DrawDebugGUI();

	//デバッグプリミティブ描画
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	//トランスフォーム更新
	void UpdateTransfom();
protected:
	//virtual void Boil(Ingredients ing) {}

	//virtual void Bake(Ingredients ing) {}

 	//virtual void Cut(Ingredients ing) {}

	//virtual void Fry(Ingredients ing) {}

};
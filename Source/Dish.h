#pragma once
#include "foodManager.h"
#include "food.h"
#include "map"
#include "set"
#include "string"
#include "System/Model.h"

class Dish
{
protected:
	std::unique_ptr<Model> modelBank[2];
	Model* model;
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

	int dishLV = 0;

	//シンクに入ってるかどうか
	bool isSink = false;
	bool isGrund = false;
private:
	Ingredients* OnDishFood;
public:
	Dish();
	~Dish();
public:
	////////////////////////////////////
	const int GetDishLV() { return dishLV; }
	void setOndishFood(Ingredients* ing) { OnDishFood = ing; }
	Ingredients* getOndishFood() { return OnDishFood; }
	virtual void setPosition(const DirectX::XMFLOAT3 pos) { position = pos; }
	virtual void setScale(const DirectX::XMFLOAT3 scale) { this->scale = scale; }
	virtual const DirectX::XMFLOAT3& getPosition() { return position; }
	const float  getRadius() { return radius; }
	DirectX::XMFLOAT4X4& getTransform() { return transform; }
	const DirectX::XMFLOAT3& getScale() { return scale; }
	const DirectX::XMFLOAT3& getAngle() { return angle; }
	const int& GetLv() const { return dishLV; }
	const void setLv(int lv) { dishLV = lv; }
	const void SetIsSink(bool i) { isSink = i; }
	const bool GetIsSink() const { return isSink; }
	const void SetIsGrund(bool b) { isGrund = b; }
	const bool GetIsGrund() { return isGrund; }
	////////////////////////////////////
	enum foodType
	{
		RICE = 0,
		ONION,
		EGG,
		TOMATO,
		CHICKENRICE,
		OMURICE,
		RICETOMATO,
		RICEONION,
	};

	Ingredients* MixDishOnFood(Ingredients* OtherIng,FoodManager* foodmanager);

	void Render(const RenderContext& rc,ModelRenderer* render);

	std::map<std::set<foodType>, foodType> recipes;

	void Update(float elapsedTime);

	void UpdateTransfom();
};
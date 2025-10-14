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

	int Lv = 0;

private:
	Ingredients* OnDishFood;

public:
	Dish();
	~Dish();
public:
	////////////////////////////////////
	void const setOndishFood(Ingredients* ing) { OnDishFood = ing; }
	virtual void setPosition(const DirectX::XMFLOAT3 pos) { position = pos; }
	virtual void setScale(const DirectX::XMFLOAT3 scale) { this->scale = scale; }
	virtual const DirectX::XMFLOAT3& getPosition() { return position; }
	const float  getRadius() { return radius; }
	DirectX::XMFLOAT4X4& getTransform() { return transform; }
	const DirectX::XMFLOAT3& getScale() { return scale; }
	const DirectX::XMFLOAT3& getAngle() { return angle; }
	const int& GetLv() { return Lv; }
	const void setLv(int lv) { Lv = lv; }
	////////////////////////////////////
	enum foodType
	{
		RICE = 0,
		CHICKING,
		CARROT,
		ONION,
		EGG,
		CHICKENRICE,
		OMURICE,
	};

	Ingredients* MixDishOnFood(Ingredients* OtherIng,FoodManager* foodmanager);
	
	void Render(const RenderContext& rc,ModelRenderer* render);

	std::map<std::set<foodType>, foodType> recipes;

	void Update(float elapsedTime);

	void UpdateTransfom();
};
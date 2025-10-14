#pragma once

#include "stage.h"
#include "Ingredients.h"
#include "DishManager.h"
#include <memory>

class Utensils : public Stage
{
protected:
	float timer[3] = { 2.0f,1.5f,1.0f };
	float cookingTimer;
	bool finish = false;
	int friendX;
	int friendY;
	bool friendOn;
	Ingredients* food;
	Dish* dish;
	bool right = false;

public:
	Utensils();
	virtual ~Utensils() override {}
public:
	////////////////////

	void SetFood(Ingredients* GetFood)
	{
		if (food != nullptr)
		{
			food = GetFood;
			cookingTimer = timer[Lv];
		}
	}

	//std::unique_ptr<Ingredients> GetFood()
	//{
	//	if (finish)
	//	{
	//		return std::move(food);
	//	}
	//	return nullptr;
	//}

	void SetFriendOn(bool o) { friendOn = o; }
	const bool GetFriendOn() const { return friendOn; }

	void SetFriendX(int x) { friendX = x; }
	void SetFriendY(int y) { friendY = y; }
	const int GetFriendX() const { return friendX; }
	const int GetFriendY() const { return friendY; }

	const bool GetRight()const { return right; }

	////////////////////
public:
	virtual void Update(float elapsedTime, FoodManager* FM) override;
	virtual void Update(float elapsedTime, DishManager* DM){};
	virtual void Render(const RenderContext& rc, ModelRenderer* renderer);
};
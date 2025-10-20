#pragma once

#include "stage.h"
#include "Ingredients.h"
#include "DishManager.h"
#include "System/AudioSource.h"
#include <memory>

class Player;

class Utensils : public Stage
{
protected:
	float timer[3] = { 2.0f,1.5f,1.0f };
	float cookingTimer;
	float cookingTimerBank;
	bool finish = false;
	int friendX;
	int friendY;
	bool friendOn;
	Ingredients* food = nullptr;
	Dish* dish = nullptr;
	bool right = false;
	float WarningTime{ 0.0f };
	float WarningTimeBank{ 1.0f };
	AudioSource* audio;
public:
	Utensils();
	virtual ~Utensils() override {}
public:
	////////////////////

	virtual bool SetFood(Ingredients* GetFood)
	{
		if (food != nullptr)
		{
			food = GetFood;
			cookingTimer = timer[Lv];
			return true;
		}
		return false;
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
	const float GetCookingTimer() { return cookingTimer; }
	const float GetCookingTimerBank() { return cookingTimerBank; }

	const float GetWarningTime() { return WarningTime; }
	const float GetWarningTimeBank() { return WarningTimeBank; }

	////////////////////
public:
	virtual void Update(float elapsedTime, FoodManager* FM, Player* P);
	virtual void Update(float elapsedTime, DishManager* DM, Player* P){}
	virtual void Render(const RenderContext& rc, ModelRenderer* renderer);
};
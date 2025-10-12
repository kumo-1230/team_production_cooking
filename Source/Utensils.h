#pragma once

#include "stage.h"
#include "Ingredients.h"

class Utensils : public Stage
{
protected:
	float timer[3] = { 2.0f,1.5f,1.0f };
	float cookingTimer;
	bool finish = false;
	int friendX;
	int friendY;
	bool friendOn;
	std::unique_ptr<Ingredients> food;
	std::vector<int> oldDish;
	std::vector<int> newDish;
public:
	Utensils();
	virtual ~Utensils() override {}
public:
	////////////////////

	std::unique_ptr<Ingredients> SetFood(std::unique_ptr<Ingredients> GetFood)
	{
		if (food != nullptr)
		{
			food = std::move(GetFood);
			cookingTimer = timer[Lv];
			return nullptr;
		}
		return std::move(GetFood);
	}

	std::unique_ptr<Ingredients> GetFood()
	{
		if (finish)
		{
			return std::move(food);
		}
		return nullptr;
	}

	void SetFriendOn(bool o) { friendOn = o; }
	const bool GetFriendOn() const { return friendOn; }

	void SetFriendX(int x) { friendX = x; }
	void SetFriendY(int y) { friendY = y; }
	const int GetFriendX() const { return friendX; }
	const int GetFriendY() const { return friendY; }

	int SetoldDish(int d)
	{
		if (d == 2)
		{
			oldDish.push_back(d);
			return NULL;
		}
		return d;
	}

	int SetNewDish(int d)
	{
		if (d == 2)
		{
			oldDish.push_back(d);
			return NULL;
		}
		return d;
	}

	////////////////////
public:
	virtual void Update(float elapsedTime) override;
};
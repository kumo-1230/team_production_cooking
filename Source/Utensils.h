#pragma once

#include "stage.h"
#include "Ingredients.h"
#include "Dish.h"
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
	std::unique_ptr<Ingredients> food;
	std::vector<std::unique_ptr<Dish>> oldDish;
	std::vector<std::unique_ptr<Dish>> newDish;
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

	//intを皿クラスに後々変更
	std::unique_ptr<Dish> SetoldDish(std::unique_ptr<Dish> d)
	{
		if (d->GetLv() == 2)
		{
			oldDish.push_back(std::move(d));
			return nullptr;
		}
		return std::move(d);
	}

	std::unique_ptr<Dish> SetNewDish(std::unique_ptr<Dish> d)
	{
		if (d->GetLv() == 1)
		{
			oldDish.push_back(std::move(d));
			return nullptr;
		}
		return std::move(d);
	}

	////////////////////
public:
	virtual void Update(float elapsedTime) override;
	virtual void Render(const RenderContext& rc, ModelRenderer* renderer);
};
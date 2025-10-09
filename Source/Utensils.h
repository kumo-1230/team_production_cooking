#pragma once

#include "stage.h"
#include "Ingredients.h"

class Utensils : public Stage
{
protected:
	float timer[3] = { 2.0f,1.5f,1.0f };
	float cookingTimer;
	bool finish = false;
	std::unique_ptr<Ingredients> food;
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
	////////////////////
public:
	virtual void Update(float elapsedTime) override;
	virtual void Render(const RenderContext& rc, ModelRenderer* renderer) override {}
	virtual void Event() override {}
};
#pragma once

#include "stage.h"
#include "Ingredients.h"

class Utensils : public Stage
{
protected:
	float timer[3] = { 2.0f,1.5f,1.0f };
	float cookingTimer;
	std::unique_ptr<Ingredients> food;
public:
	Utensils();
	virtual ~Utensils() override {}
public:
	////////////////////

	void SetFood(std::unique_ptr<Ingredients> GetFood)
	{
		if (food != nullptr)
		{
			food = std::move(GetFood);
			cookingTimer = timer[Lv];
		}
	}

	////////////////////
public:
	virtual void Update(float elapsedTime) override {}
	virtual void Render(const RenderContext& rc, ModelRenderer* renderer) override {}
	virtual void Event() override {}
	virtual bool Cooking() { return false; }
};
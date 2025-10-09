#include "foodManager.h"

void FoodManager::Update(float elapsedTime)
{
	for (auto& a : foods)
	{
		a->Update(elapsedTime);
	}
}

void FoodManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	for (auto& a : foods)
	{
		a->Render(rc, renderer);
	}
}

void FoodManager::Register(std::unique_ptr<Ingredients> ing)
{
	foods.push_back(std::move(ing));
}

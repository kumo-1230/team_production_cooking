#include "foodManager.h"

void FoodManager::Update(float elapsedTime)
{
	for (Ingredients* a : foods)
	{
		a->Update(elapsedTime);
	}
}

void FoodManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	for (Ingredients* a : foods)
	{
		a->Render(rc, renderer);
	}
}

void FoodManager::Register(Ingredients* ing)
{
	foods.push_back(ing);
}

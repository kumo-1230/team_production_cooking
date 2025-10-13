#include "DishManager.h"

void DishManager::Update(float elapsedTime)
{
	for (auto& a : dishes)
	{
		a.get()->Update(elapsedTime);
	}
}

void DishManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	for (auto& a : dishes)
	{
		a.get()->Render(rc,renderer);
	}
}

void DishManager::Register(std::unique_ptr<Dish> dish)
{
	dishes.push_back(std::move(dish));
}

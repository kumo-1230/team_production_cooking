#include "foodManager.h"

void FoodManager::Update(float elapsedTime)
{
	for (auto& a : foods)
	{
		a->Update();
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

void FoodManager::RemoveFood(Ingredients* removeIng)
{
	//ごめんここ書き方思いつかな過ぎてチャットGPTに投げた
	if (!removeIng) return;
	bool removed = false;

	for(auto it = foods.begin();it!=foods.end();)
	{
		if (it->get() == removeIng)
		{
			it = foods.erase(it);
			removed = true;
		}
		else
		{
			++it;
		}
	}
}

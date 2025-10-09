#pragma once
#include "food.h"

class FoodManager
{
private:
	std::vector<std::unique_ptr<Ingredients>> foods;
public:
	FoodManager() {}
	~FoodManager() {}
public:
	Ingredients* GetFood(int i) const { return foods[i].get(); }

	int GetFoodCount() const { return static_cast<int> (foods.size()); }
	/////////
public:
	void Update(float elapsedTime);

	void Render(const RenderContext& rc, ModelRenderer* renderer);

	void Register(std::unique_ptr<Ingredients> ing);
};
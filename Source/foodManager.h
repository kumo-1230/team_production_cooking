#pragma once
#include "food.h"

class FoodManager
{
private:
	std::vector<Ingredients*> foods;
public:
	FoodManager() {}
	~FoodManager() {}
public:
	/////////
	Ingredients* GetFood(int i) const { return foods.at(i); }

	int GetFoodCount() const { return static_cast<int> (foods.size()); }
	/////////
public:
	void Update(float elapsedTime);

	void Render(const RenderContext& rc, ModelRenderer* renderer);

	void Register(Ingredients* ing);
};
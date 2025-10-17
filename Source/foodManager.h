#pragma once
#include "food.h"

class FoodManager
{
private:
	std::vector<std::unique_ptr<Ingredients>> foods;
	//std::unique_ptr<Sprite> tomato;
	//std::unique_ptr<Sprite> onion;
	//std::unique_ptr<Sprite> ;
public:
	FoodManager() {}
	~FoodManager() {}
public:
	Ingredients* GetFood(int i) const { return foods[i].get(); }

	void SetFood(std::unique_ptr<Ingredients> f) { foods.push_back(std::move(f)); }

	int GetFoodCount() const { return static_cast<int> (foods.size()); }

	void Register(std::unique_ptr<Ingredients> ing);

	void RemoveFood(Ingredients* removeIng);
	/////////
public:
	void Update(float elapsedTime);

	void Render(const RenderContext& rc, ModelRenderer* renderer);

	void Render2D(const RenderContext& rc);

};
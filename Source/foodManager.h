#pragma once
#include "food.h"
#include "System/Sprite.h"

class FoodManager
{
private:
	std::vector<std::unique_ptr<Ingredients>> foods;
	std::unique_ptr<Sprite> SpriteTomato = nullptr;
	std::unique_ptr<Sprite> SpriteOnion = nullptr;
	std::unique_ptr<Sprite> SpriteEgg = nullptr;
	std::unique_ptr<Sprite> SpriteRice = nullptr;
public:
	FoodManager()
	{
		SpriteTomato = std::make_unique<Sprite>(("Data/Sprite/tomato_Icon.png"));
		SpriteOnion = std::make_unique<Sprite>(("Data/Sprite/onion_Icon.png"));
		SpriteEgg = std::make_unique<Sprite>(("Data/Sprite/egg_Icon.png"));
		SpriteRice = std::make_unique<Sprite>(("Data/Sprite/rice_Icon.png"));
	}
	~FoodManager() {}
public:
	Ingredients* GetFood(int i) const { return foods[i].get(); }

	void SetFood(std::unique_ptr<Ingredients> f) { foods.push_back(std::move(f)); }

	int GetFoodCount() const { return static_cast<int> (foods.size()); }

	void Register(std::unique_ptr<Ingredients> ing);

	void RemoveFood(Ingredients* removeIng);

	void RemoveAllFood() { foods.clear(); }
	/////////
public:
	void Update(float elapsedTime);

	void Render(const RenderContext& rc, ModelRenderer* renderer);

	void Render2D(const RenderContext& rc);

};
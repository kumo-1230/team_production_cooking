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
	std::unique_ptr<Sprite> SpriteChikenrice = nullptr;
	std::unique_ptr<Sprite> SpriteChikenriceGreen = nullptr;
	std::unique_ptr<Sprite> SpriteChikenriceTomato = nullptr;

	float time = 0.0f;
	float frequency = 0.3f;
	float amplitude = 5.0f;
public:
	FoodManager()
	{
		SpriteTomato = std::make_unique<Sprite>(("Data/Sprite/tomato_Icon.png"));
		SpriteOnion = std::make_unique<Sprite>(("Data/Sprite/UI/greenpepper_icon.png"));
		SpriteEgg = std::make_unique<Sprite>(("Data/Sprite/egg_Icon.png"));
		SpriteRice = std::make_unique<Sprite>(("Data/Sprite/rice_Icon.png"));
		SpriteChikenrice = std::make_unique<Sprite>("Data/Sprite/UI/chikenrice_greenpepper_icon.png");
		SpriteChikenriceGreen = std::make_unique<Sprite>("Data/Sprite/UI/rice_greenpepper.png");
		SpriteChikenriceTomato = std::make_unique<Sprite>("Data/Sprite/UI/chickenrice_icon.png");
	}
	~FoodManager() {}
public:
	Ingredients* GetFood(int i) const { return foods[i].get(); }

	Ingredients* SetFood(std::unique_ptr<Ingredients> f) { return foods.emplace_back(std::move(f)).get(); }

	int GetFoodCount() const { return static_cast<int> (foods.size()); }

	void Register(std::unique_ptr<Ingredients> ing);

	void RemoveFood(Ingredients* removeIng);

	void RemoveAllFood() { foods.clear(); }
	/////////

public:
	void Update(float elapsedTime);

	void Render(const RenderContext& rc, ModelRenderer* renderer);

	void Render2D(const RenderContext& rc);
private:
	float SinPosY();
};
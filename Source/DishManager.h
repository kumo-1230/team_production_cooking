#pragma once
#include "Dish.h"
#include <memory>
#include <vector>

class DishManager
{
private:
	std::vector <std::unique_ptr<Dish>> dishes;
public:
	DishManager(){}
	~DishManager(){}
	Dish* getDish(int i) const { return dishes[i].get(); }
	int getDishNum() const { return dishes.size(); }
public:
	void Update(float elapsedTime);

	void Render(const RenderContext& rc, ModelRenderer* renderer);

	void Register(std::unique_ptr<Dish> dish);
};
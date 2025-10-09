#pragma once
#include "foodManager.h"
#include "food.h"

class Dish
{
private:
	std::unique_ptr<Ingredients> OnDishFood;
public:
	void MixDishOnFood(Ingredients ing);
};
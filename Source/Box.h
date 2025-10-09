#pragma once
#include "stage.h"
#include "food.h"

class Box :public Stage
{
private:
	std::unique_ptr<Ingredients> myIng;
private:
	Ingredients* TakeIngredients();
};
#pragma once
#include "Utensils.h"
#include "Ingredients.h"
#include "SceneGame.h"

class Submission : public Utensils
{
public:
	Submission(const DirectX::XMFLOAT3& pos, int lv);
	~Submission(){}
public:
	int submit(Ingredients* ing, Dish* dish, FoodManager* foodManager);

	void Render(const RenderContext& rc, ModelRenderer* renderer);
};
#pragma once

#include "Utensils.h"

class CreateDishBox : public Utensils
{
private:
	int dishCount;
public:
	CreateDishBox(const DirectX::XMFLOAT3& pos, int lv);
	~CreateDishBox();
public:
	void Update(float elapsedTime, DishManager* DM) override;
	void Render(const RenderContext& rc, ModelRenderer* renderer)override;
};
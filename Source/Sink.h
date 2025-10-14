#pragma once

#include "Utensils.h"

class Sink : public Utensils
{
private:
	int dishCount = 0;
	float cookingTimerBank;
public:
	Sink(const DirectX::XMFLOAT3& pos, int lv, bool R);
	~Sink();
public:
	void Update(float elapsedTime,DishManager* DM) override;
	void Render(const RenderContext& rc, ModelRenderer* renderer)override;
};
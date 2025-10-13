#pragma once

#include "Utensils.h"

class Sink : public Utensils
{
private:
	bool right = false;
	int dishCount = 0;
	float cookingTimerBank;
public:
	Sink(const DirectX::XMFLOAT3& pos, int lv, bool R);
	~Sink();
public:
	void Update(float elapsedTime) override;
	void Render(const RenderContext& rc, ModelRenderer* renderer)override;
};
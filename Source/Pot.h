#pragma once
#include "Utensils.h"

class Pot : public Utensils
{
public:
	Pot(const DirectX::XMFLOAT3& pos, int lv);
	~Pot() override;

	//‰Šú‰»
	void Initialize() override;
};
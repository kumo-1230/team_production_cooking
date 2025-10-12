#pragma once
#include "Utensils.h"

class Stove : public Utensils
{
public:
	Stove(const DirectX::XMFLOAT3& pos, int lv);
	~Stove() override;

	//‰Šú‰»
	void Initialize() override;
};
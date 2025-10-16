#pragma once
#include "Utensils.h"

class Pot : public Utensils
{
public:
	Pot(const DirectX::XMFLOAT3& pos, int lv);
	~Pot() override;

	//‰Šú‰»
	void Initialize() override;
public:
	bool SetFood(Ingredients* GetFood) override
	{
		if (food == nullptr && GetFood != nullptr)
		{
			if (foodType::RICE == GetFood->GetType() && GetFood->GetLv() == 0)
			{
				food = GetFood;
				cookingTimer = timer[Lv];
				return true;
			}
		}
		return false;
	}

};
#pragma once
#include "Utensils.h"

class Stove : public Utensils
{
public:
	Stove(const DirectX::XMFLOAT3& pos, int lv);
	~Stove() override;

	//‰Šú‰»
	void Initialize() override;
public:
	bool SetFood(Ingredients* GetFood) override
	{
		if (food == nullptr && GetFood != nullptr)
		{
			if (foodType::ONION == GetFood->GetType() && GetFood->GetLv() == 1 ||
				foodType::EGG == GetFood->GetType() && GetFood->GetLv() == 0)
			{
				food = GetFood;
				cookingTimer = timer[Lv];
				return true;
			}
		}
		return false;
	}

};
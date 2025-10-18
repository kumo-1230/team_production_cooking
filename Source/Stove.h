#pragma once
#include "Utensils.h"

class Stove : public Utensils
{
public:
	Stove(const DirectX::XMFLOAT3& pos, int lv, bool Long, bool right);
	~Stove() override;

	//‰Šú‰»
	void Initialize() override;
public:
	bool SetFood(Ingredients* GetFood) override
	{
		if (food == nullptr && GetFood != nullptr)
		{
			if (foodType::ONION == GetFood->GetType() && GetFood->GetLv() == 1 ||
				foodType::TOMATO == GetFood->GetType() && GetFood->GetLv() == 1 ||
				foodType::EGG == GetFood->GetType() && GetFood->GetLv() ==	1)
			{
				food = GetFood;
				cookingTimer = 0;
				cookingTimerBank = timer[Lv];
				DirectX::XMFLOAT3 s{ 0.1f,0.1f,0.1f };
				GetFood->setScale(s);
				GetFood->UpdateTransfom();
				return true;
			}
		}
		return false;
	}

};
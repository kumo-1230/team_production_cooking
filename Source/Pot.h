#pragma once
#include "Utensils.h"

class Pot : public Utensils
{
public:
	Pot(const DirectX::XMFLOAT3& pos, int lv, bool Long, bool right);
	~Pot() override;

	//‰Šú‰»
	void Initialize() override;
public:
	bool SetFood(Ingredients* GetFood) override
	{
		if (food == nullptr && GetFood != nullptr)
		{
			if (foodType::RICE == GetFood->GetType() && GetFood->GetLv() == 1)
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
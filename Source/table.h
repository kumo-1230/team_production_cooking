#pragma once
#include "Utensils.h"

class Table : public Utensils
{
private:
	float stopTimer = 0.0f;
public:
	Table(const DirectX::XMFLOAT3& pos, int lv, bool Long, bool right)
	{
		position = pos;
		Lv = 1;
		friendOn = Long;
		model = std::make_unique<Model>("Data/Model/Utensils/desk.mdl");
		scale = { 0.1f,0.1f,0.1f };
		UpdateTransform();
	}
	~Table() override {}

	//èâä˙âª
	void Initialize() override {}

public:
	bool SetFood(Ingredients* GetFood) override
	{
		if (food == nullptr && GetFood != nullptr && stopTimer <= 0)
		{
			{
				food = GetFood;
				cookingTimer = 0;
				cookingTimerBank = timer[Lv];
				DirectX::XMFLOAT3 s{ 0.1f,0.1f,0.1f };
				GetFood->setScale(s);
				GetFood->UpdateTransfom();
				stopTimer = 0.5f;
				return true;
			}
		}
		return false;
	}
	void Update(float elapsedTime, FoodManager* FM, Player* P)override
	{
		stopTimer -= 1 * elapsedTime;
		if (food != nullptr)
		{
			{
				DirectX::XMFLOAT3 pos{ position };
				pos.y += 2.0f;
				food->setPosition(pos);
			}
			if (P->getIng() == food && food != nullptr)
			{
				food = nullptr;

				stopTimer = 0.5f;
			}
		}

	};

};
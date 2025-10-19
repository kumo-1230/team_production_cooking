#pragma once

#include "Utensils.h"
#include "foodManager.h"
#include "Player.h"

class KetuchupBox : public  Utensils
{
public:
	KetuchupBox(DirectX::XMFLOAT3 pos, int m)
	{
		position = pos;
		mode = m;
		Initialize();
	}
	~KetuchupBox() override {}

	//èâä˙âª
	void Initialize()override
	{
		model = std::make_unique<Model>("Data/Model/Box/sauce/sourceTomato.mdl");
		scale = { 0.1f,0.1f,0.1f };
		angle = { 0,DirectX::XMConvertToRadians(180),0 };
		UpdateTransform();
	}
public:
	bool SetFood(Ingredients* GetFood) override
	{
		if (food == nullptr && GetFood != nullptr)
		{
			if (foodType::OMURICE == GetFood->GetType() && GetFood->GetOmuType() == 0)
			{
				food = GetFood;
				cookingTimer = 0;
				cookingTimerBank = 0.3f;
				DirectX::XMFLOAT3 s{ 0.1f,0.1f,0.1f };
				GetFood->setScale(s);
				GetFood->UpdateTransfom();
				return true;
			}
		}
		return false;
	}

public:
	void Update(float elapsedTime, FoodManager* FM, Player* P)override
	{
		if (food != nullptr)
		{
			cookingTimer += 1 * elapsedTime;
			finish = (cookingTimer >= cookingTimerBank);
			if (finish == true)
			{
				DirectX::XMFLOAT3 pos{ position };
				pos.y += 2.0f;
				food->setPosition(pos);
				cookingTimer = cookingTimerBank;
			}
			if (P->getIng() == food)
			{
				food->SetOmuType(1);
				food->setPosition(P->getDish()->getPosition());
				food = nullptr;
				cookingTimer = 0;
			}
		}

	}
};

class DemiBox : public  Utensils
{
public:
	DemiBox(DirectX::XMFLOAT3 pos, int m)
	{
		position = pos;
		mode = m;
		Initialize();
	}
	~DemiBox() override {}

	//èâä˙âª
	void Initialize()override
	{
		model = std::make_unique<Model>("Data/Model/Box/sauce/sourceDemi.mdl");
		scale = { 0.1f,0.1f,0.1f };
		angle = { 0,DirectX::XMConvertToRadians(180),0 };
		UpdateTransform();
	}
public:
	bool SetFood(Ingredients* GetFood) override
	{
		if (food == nullptr && GetFood != nullptr)
		{
			if (foodType::OMURICE == GetFood->GetType() && GetFood->GetOmuType() == 0)
			{
				food = GetFood;
				cookingTimer = 0;
				cookingTimerBank = 0.3f;
				DirectX::XMFLOAT3 s{ 0.1f,0.1f,0.1f };
				GetFood->setScale(s);
				GetFood->UpdateTransfom();
				return true;
			}
		}
		return false;
	}

public:
	void Update(float elapsedTime, FoodManager* FM, Player* P)override
	{
		if (food != nullptr)
		{
			cookingTimer += 1 * elapsedTime;
			finish = (cookingTimer >= cookingTimerBank);
			if (finish == true)
			{
				DirectX::XMFLOAT3 pos{ position };
				pos.y += 2.0f;
				food->setPosition(pos);
				cookingTimer = cookingTimerBank;
			}
			if (P->getIng() == food)
			{
				food->SetOmuType(2);
				food->setPosition(P->getDish()->getPosition());
				food = nullptr;
				cookingTimer = 0;
			}
		}

	}
};

class WhiteBox : public  Utensils
{
public:
	WhiteBox(DirectX::XMFLOAT3 pos, int m)
	{
		position = pos;
		mode = m;
		Initialize();
	}
	~WhiteBox() override {}

	//èâä˙âª
	void Initialize()override
	{
		model = std::make_unique<Model>("Data/Model/Box/sauce/sourceWhite.mdl");
		scale = { 0.1f,0.1f,0.1f };
		angle = { 0,DirectX::XMConvertToRadians(180),0 };
		UpdateTransform();
	}
public:
	bool SetFood(Ingredients* GetFood) override
	{
		if (food == nullptr && GetFood != nullptr)
		{
			if (foodType::OMURICE == GetFood->GetType() && GetFood->GetOmuType() == 0)
			{
				food = GetFood;
				cookingTimer = 0;
				cookingTimerBank = 0.3f;
				DirectX::XMFLOAT3 s{ 0.1f,0.1f,0.1f };
				GetFood->setScale(s);
				GetFood->UpdateTransfom();
				return true;
			}
		}
		return false;
	}

public:
	void Update(float elapsedTime, FoodManager* FM, Player* P)override
	{
		if (food != nullptr)
		{
			cookingTimer += 1 * elapsedTime;
			finish = (cookingTimer >= cookingTimerBank);
			if (finish == true)
			{
				DirectX::XMFLOAT3 pos{ position };
				pos.y += 2.0f;
				food->setPosition(pos);
				cookingTimer = cookingTimerBank;
			}
			if (P->getIng() == food)
			{
				food->SetOmuType(3);
				food->setPosition(P->getDish()->getPosition());
				food = nullptr;
				cookingTimer = 0;
			}
		}

	}
};
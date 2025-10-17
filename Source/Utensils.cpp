#include "Utensils.h"
#include "Player.h"

Utensils::Utensils()
{
	food = nullptr;
}

void Utensils::Update(float elapsedTime, FoodManager* FM, Player* P)
{
	if (food != nullptr)
	{
		cookingTimer += 1 * elapsedTime;
		finish = (cookingTimer >= cookingTimerBank);
		if (finish)
		{
			DirectX::XMFLOAT3 pos{ position };
			pos.y += 2.0f;
			food->setPosition(pos);
			cookingTimer = cookingTimerBank;
			if (Lv == 1)
			{
				WarningTime += 1 * elapsedTime;
				if (WarningTime > WarningTimeBank)
				{
					//Žg‚¦‚È‚­‚È‚Á‚½‚Æ‚«
					FM->RemoveFood(food);
					food = nullptr;
					WarningTime = 0;
					cookingTimer = 0;
				}
			}
		}
		if (P->getIng() == food && food != nullptr)
		{
			if (finish)
			{
				food->AddLv();
			}
			food = nullptr;
			cookingTimer = 0;
			WarningTime = 0;
		}
	}
}

//•`‰æˆ—
void Utensils::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	//ƒŒƒ“ƒ_ƒ‰‚Éƒ‚ƒfƒ‹‚ð•`‰æ‚µ‚Ä‚à‚ç‚¤
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);
}

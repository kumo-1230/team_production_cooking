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
		if (finish == true)
		{
			DirectX::XMFLOAT3 pos{ position };
			pos.y += 2.0f;
			food->setPosition(pos);
			if (Lv == 1)
			{
				if (cookingTimer > cookingTimerBank + 1)
				{
					//Žg‚¦‚È‚­‚È‚Á‚½‚Æ‚«
					FM->RemoveFood(food);
					food = nullptr;
					cookingTimer = 0;
				}
			}
			else
			{
				cookingTimer = cookingTimerBank;
			}
		}
		if (P->getIng() == food && food != nullptr)
		{
			food->AddLv();
			food = nullptr;
			cookingTimer = 0;
		}
	}
}

//•`‰æˆ—
void Utensils::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	//ƒŒƒ“ƒ_ƒ‰‚Éƒ‚ƒfƒ‹‚ð•`‰æ‚µ‚Ä‚à‚ç‚¤
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);
}

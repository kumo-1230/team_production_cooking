#include "Utensils.h"

Utensils::Utensils()
{
	food = nullptr;
}

void Utensils::Update(float elapsedTime, FoodManager* FM)
{
	if (food != nullptr)
	{
		cookingTimer -= 1 * elapsedTime;
		finish = (cookingTimer <= 0);
		if (finish == true)
		{
			food->SetLv(2);
			if (Lv == 1)
			{
				if (cookingTimer < -1.0f)
				{
					//Žg‚¦‚È‚­‚È‚Á‚½‚Æ‚«
					food->SetLv(4);
				}
			}
		}
	}
}

//•`‰æˆ—
void Utensils::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	//ƒŒƒ“ƒ_ƒ‰‚Éƒ‚ƒfƒ‹‚ð•`‰æ‚µ‚Ä‚à‚ç‚¤
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);
}

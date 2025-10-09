#include "Utensils.h"

Utensils::Utensils()
{
	food = nullptr;
}

void Utensils::Update(float elapsedTime)
{
	if (food != nullptr && food->GetLv() == 1)
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
					food->SetLv(4);
				}
			}
		}
	}
}

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
					//�g���Ȃ��Ȃ����Ƃ�
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

//�`�揈��
void Utensils::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	//�����_���Ƀ��f����`�悵�Ă��炤
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);
}

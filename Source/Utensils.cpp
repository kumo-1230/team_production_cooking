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
					//�g���Ȃ��Ȃ����Ƃ�
					food->SetLv(4);
				}
			}
		}
	}
}

//�`�揈��
void Utensils::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	//�����_���Ƀ��f����`�悵�Ă��炤
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);
}

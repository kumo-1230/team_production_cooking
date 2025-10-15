#include "CreateDishBox.h"

//すべての器具を回すときにこのクラスを見つけた時セット皿の配列を回してLv2の物をすべてセットする

CreateDishBox::CreateDishBox(const DirectX::XMFLOAT3& pos, int lv)
{
	model = std::make_unique<Model>("Data/Model/gasukonro.mdl");
	Lv = lv;
	if (Lv == 2)
	{
		Lv = 3;
	}
	position = pos;
	scale = { 0.1f,0.1f,0.1f };
	UpdateTransform();

}

CreateDishBox::~CreateDishBox()
{
}

void CreateDishBox::Update(float elapsedTime, DishManager* DM)
{
	DirectX::XMFLOAT3 p = { position.x,position.y + 2.2f,position.z};
	for (int i = 0; i < DM->getDishNum(); i++)
	{
		if (DM->getDish(i)->GetIsSink() == false && DM->getDish(i)->GetDishLV() == 1)
		{
			p.y += 0.5f * i;
			//皿のポジションをセット
			DM->getDish(i)->setPosition(p);
		}
	}
}

void CreateDishBox::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	Utensils::Render(rc, renderer);
}

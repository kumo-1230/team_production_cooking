#include "CreateDishBox.h"

//���ׂĂ̊����񂷂Ƃ��ɂ��̃N���X�����������Z�b�g�M�̔z����񂵂�Lv2�̕������ׂăZ�b�g����

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

void CreateDishBox::Update(float elapsedTime)
{
	DirectX::XMFLOAT3 p = { position.x,2.0f,position.z};
	for (int i = 0; i < oldDish.size(); i++)
	{
		p.y += 0.5f * i;
		//�M�̃|�W�V�������Z�b�g
		oldDish[i]->setPosition(p);
	}
}

void CreateDishBox::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	Utensils::Render(rc, renderer);
	if (oldDish.size() != 0)
	{
		for (const auto& d : newDish)
		{
			//�M�̃����_�[
			d->Render(rc, renderer);
		}
	}
}

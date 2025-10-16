#include "CreateDishBox.h"
#include <imgui.h>
#include "Player.h"

//���ׂĂ̊����񂷂Ƃ��ɂ��̃N���X�����������Z�b�g�M�̔z����񂵂�Lv2�̕������ׂăZ�b�g����

#define DEBUG

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

void CreateDishBox::Update(float elapsedTime, DishManager* DM, Player* P)
{
	DirectX::XMFLOAT3 p = { position.x,position.y + 2.0f,position.z};
	for (int i = 0; i < DM->getDishNum(); i++)
	{
		if (DM->getDish(i)->GetIsSink() == false && DM->getDish(i)->GetDishLV() == 1)
		{
			p.y += 0.5f * i;
			//�M�̃|�W�V�������Z�b�g
			DM->getDish(i)->setPosition(p);
		}
	}
}

void CreateDishBox::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	Utensils::Render(rc, renderer);
#ifdef DEBUG
	//�Ȃ񂩂̃|�W�V����������Ă���
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	//�\���ꏊ
	ImGui::SetNextWindowPos(ImVec2(pos.x + 100, pos.y + 100), ImGuiCond_Once);
	//�傫��
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("CreateDishBox", nullptr, ImGuiWindowFlags_None))
	{
		//�g�����X�t�H�[��
		//if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::InputFloat3("pos", &position.x);
		}
	}
	ImGui::End();

#endif // DEBUG

}

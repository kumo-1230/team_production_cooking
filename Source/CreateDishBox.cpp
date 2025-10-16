#include "CreateDishBox.h"
#include <imgui.h>
#include "Player.h"

//すべての器具を回すときにこのクラスを見つけた時セット皿の配列を回してLv2の物をすべてセットする

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
			//皿のポジションをセット
			DM->getDish(i)->setPosition(p);
		}
	}
}

void CreateDishBox::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	Utensils::Render(rc, renderer);
#ifdef DEBUG
	//なんかのポジションを取ってくる
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	//表示場所
	ImGui::SetNextWindowPos(ImVec2(pos.x + 100, pos.y + 100), ImGuiCond_Once);
	//大きさ
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("CreateDishBox", nullptr, ImGuiWindowFlags_None))
	{
		//トランスフォーム
		//if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::InputFloat3("pos", &position.x);
		}
	}
	ImGui::End();

#endif // DEBUG

}

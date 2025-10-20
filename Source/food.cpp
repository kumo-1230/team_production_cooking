#include "food.h"

#include <imgui.h>

#define DEBUG

Rice::Rice()
{
	myFoodType = foodType::RICE;
	models[0] = std::make_unique<Model>("Data/Model/kome/namagome.mdl");
	models[1] = std::make_unique<Model>("Data/Model/kome/rice.mdl");
	models[2] = std::make_unique<Model>("Data/Model/kome/namagome.mdl");
	
	scale.x = scale.y = scale.z = 0.1f;
	nowLV = 1;
	UpdateTransfom();
}

Rice::~Rice()
{
}


void Rice::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model, ShaderId::Lambert);
}

void Rice::Update()
{	
	model = models[nowLV].get();
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}


Onion::Onion()
{
	models[0] = std::make_unique<Model>("Data/Model/onion/onionLv1.mdl");
	models[1] = std::make_unique<Model>("Data/Model/onion/onionLv2.mdl");
	models[2] = std::make_unique<Model>("Data/Model/onion/onionLv3.mdl");
	myFoodType = foodType::ONION;
	scale.x = scale.y = scale.z = 0.1f;
	UpdateTransfom();
}

Onion::~Onion()
{
}

void Onion::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model, ShaderId::Lambert);
}

void Onion::Update()
{
	model = models[nowLV].get();
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

Egg::Egg()
{
	models[0] = std::make_unique<Model>("Data/Model/egg/tamago.mdl");
	models[1] = std::make_unique<Model>("Data/Model/egg/egg.mdl");
	models[2] = std::make_unique<Model>("Data/Model/egg/yakitamago.mdl");
	myFoodType = foodType::EGG;
	scale.x = scale.y = scale.z = 0.1f;
	nowLV = 1;
	UpdateTransfom();
}

Egg::~Egg()
{
}

void Egg::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model, ShaderId::Lambert);
}

void Egg::Update()
{
	model = models[nowLV].get();
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

ChickenRice::ChickenRice()
{
	myFoodType = foodType::CHICKENRICE;
	scale.x = scale.y = scale.z = 0.1f;
	models[0] = std::make_unique<Model>("Data/Model/chickenrice/chickenrice.mdl");
	models[1] = std::make_unique<Model>("Data/Model/Slime/Slime.mdl");
	models[2] = std::make_unique<Model>("Data/Model/chickenrice/chickenriceWithOnion.mdl");
	nowLV = 2;
	model = models[omuType].get();
	UpdateTransfom();
}

ChickenRice::~ChickenRice()
{
}

void ChickenRice::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model, ShaderId::Lambert);
}

void ChickenRice::Update()
{
	model = models[omuType].get();
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

Tomato::Tomato()
{
	myFoodType = foodType::TOMATO;
	models[0] = std::make_unique<Model>("Data/Model/tomato/tomato.mdl");
	models[1] = std::make_unique<Model>("Data/Model/tomato/cut_tamato.mdl");
	models[2] = std::make_unique<Model>("Data/Model/tomato/tomato_sauce.mdl");
	scale.x = scale.y = scale.z = 0.1f;
	nowLV = 0;
	UpdateTransfom();
}

Tomato::~Tomato()
{
}

void Tomato::Render(const RenderContext& rc, ModelRenderer* render)
{
	if (nowLV == 1)
	{
		int a = 0;
	}
	render->Render(rc, transform, model, ShaderId::Lambert);
#ifdef DEBUG
	//なんかのポジションを取ってくる
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	//表示場所
	ImGui::SetNextWindowPos(ImVec2(pos.x + 300, pos.y + 300), ImGuiCond_Once);
	//大きさ
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Tomato", nullptr, ImGuiWindowFlags_None))
	{
		//トランスフォーム
		//if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::InputFloat3("position", &position.x);
			ImGui::InputFloat3("scale", &scale.x);
			ImGui::InputInt("Lv", &nowLV);
		}
	}
	ImGui::End();

#endif // DEBUG

}

void Tomato::Update()
{
	model = models[nowLV].get();
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

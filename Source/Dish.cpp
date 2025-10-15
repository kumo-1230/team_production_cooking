#include "Dish.h"
#include "omurice.h"
#include "System/ImGuiRenderer.h"
#include <imgui.h>

#define DEBUG

Dish::Dish()
{
	model.reset(new Model("Data/Model/Plate.mdl"));
	scale.x =scale.y = scale.z = 0.1f;
	dishLV = 0;
	//レシピを書いていきます(setを使うことで順番を無視)
	recipes = {
	{ {foodType::EGG,foodType::CHICKENRICE},foodType::OMURICE }
	};

}

Dish::~Dish()
{
}

Ingredients* Dish::MixDishOnFood(Ingredients* otherIng,FoodManager* foodmanager)
{
	if (!otherIng)return nullptr;
	//食材を皿の上で混ぜ合わせる処理
	if (OnDishFood)
	{
		std::set<foodType> recipe = {static_cast <foodType>(OnDishFood->GetType()),static_cast<foodType>(otherIng->GetType()) };
		auto it = recipes.find(recipe);
		if (it != recipes.end()) //レシピが見つかったら
		{
			if (OnDishFood->GetLv() == 2 && otherIng->GetLv() == 2)
			{
				//合成結果
				auto newFood = std::make_unique<omurice>();
				newFood->setScale(scale);
				newFood->setPosition(position);

				Ingredients* ing = newFood.get();
				//古いの消して新しいの入れる
				foodmanager->RemoveFood(OnDishFood);
				foodmanager->RemoveFood(otherIng);
				foodmanager->Register(std::move(newFood));
				//OnDishFood = nullptr;
				return ing;
			}
		}
	}
	return OnDishFood;
}

void Dish::Render(const RenderContext& rc,ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
#ifdef DEBUG
	//なんかのポジションを取ってくる
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	//表示場所
	ImGui::SetNextWindowPos(ImVec2(pos.x + 100, pos.y + 100), ImGuiCond_Once);
	//大きさ
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Dish", nullptr, ImGuiWindowFlags_None))
	{
		//トランスフォーム
		//if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::InputFloat3("pos", &position.x);
			ImGui::InputInt("Lv", &dishLV);

		}
	}
	ImGui::End();

#endif // DEBUG

}

void Dish::Update(float elapsedTime)
{
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

void Dish::UpdateTransfom()
{
	//スケール行列制作
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	//回転行列を制作
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	//位置行列を作成
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//三つの行列を組み合わせてワールド行列を作成
	DirectX::XMMATRIX W = S * R * T;

	//計算したワールド行列を取り出す
	DirectX::XMStoreFloat4x4(&transform, W);
}

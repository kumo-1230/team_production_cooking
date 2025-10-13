#include "Dish.h"
#include "omurice.h"


Dish::Dish()
{
	model.reset(new Model("Data/Model/Slime/Slime.mdl"));
	scale.x = scale.y = scale.z = 0.01f;

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

				OnDishFood = nullptr;
				return ing;
			}
		}
	}
	return otherIng;
}

void Dish::Render(const RenderContext& rc,ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
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

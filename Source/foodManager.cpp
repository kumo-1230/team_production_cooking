#include "foodManager.h"

void FoodManager::Update(float elapsedTime)
{
	for (auto& a : foods)
	{
		a->Update();
	}
}

void FoodManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	for (auto& a : foods)
	{
		a->Render(rc, renderer);
	}
}

void FoodManager::Render2D(const RenderContext& rc)
{
	//for (int i = 0; i < foods.size(); i++)
	//{
	//	if (foods[i].get() != nullptr)
	//	{
	//		// スクリーンサイズ取得
	//		float screenWidth = Graphics::Instance().GetScreenWidth();
	//		float screenHeight = Graphics::Instance().GetScreenHeight();

	//		DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&rc.view);
	//		DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&rc.projection);
	//		DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();

	//		//頭上のワールド座標
	//		DirectX::XMFLOAT3 spritPosition = foods[i]->GetPosition();
	//		spritPosition.y += 3.0f;

	//		//ワールド座標からスクリーン座標に変換
	//		DirectX::XMVECTOR ScreenPosition, WorldPosition;
	//		WorldPosition = DirectX::XMLoadFloat3(&spritPosition);

	//		ScreenPosition = DirectX::XMVector3Project(
	//			WorldPosition,
	//			0.0f, 0.0f,
	//			screenWidth, screenHeight,
	//			0.0f, 1.0f,
	//			Projection,
	//			View,
	//			World
	//		);

	//		//スクリーン座標
	//		DirectX::XMFLOAT2 screenPosition;
	//		DirectX::XMStoreFloat2(&screenPosition, ScreenPosition);

	//		//ゲージ描画
	//		const float grugeWidth = 30.0f;
	//		const float grugeHeight = 5.0f;

	//		sprite->Render(rc,
	//			screenPosition.x - grugeWidth / 2, screenPosition.y,
	//			0.0f,
	//			grugeWidth, grugeHeight,
	//			0.0f,
	//			1.0f, 1.0f, 1.0f, 1.0f);
	//	}
	//}
}

void FoodManager::Register(std::unique_ptr<Ingredients> ing)
{
	foods.push_back(std::move(ing));
}

void FoodManager::RemoveFood(Ingredients* removeIng)
{
	//ごめんここ書き方思いつかな過ぎてチャットGPTに投げた
	if (!removeIng) return;
	bool removed = false;

	for(auto it = foods.begin();it!=foods.end();)
	{
		if (it->get() == removeIng)
		{
			it = foods.erase(it);
			removed = true;
		}
		else
		{
			++it;
		}
	}
}

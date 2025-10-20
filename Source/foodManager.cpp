#include "foodManager.h"
#include <cmath>
#include <imgui.h>

//#define DEBUG

void FoodManager::Update(float elapsedTime)
{
	time += 1 * elapsedTime;
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
	for (int i = 0; i < foods.size(); i++)
	{
		if (foods[i].get() != nullptr)
		{
			if (foods[i]->GetIsGrund() == false)
			{
				continue;
			}
			// スクリーンサイズ取得
			float screenWidth = Graphics::Instance().GetScreenWidth();
			float screenHeight = Graphics::Instance().GetScreenHeight();

			DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&rc.view);
			DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&rc.projection);
			DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();

			//頭上のワールド座標
			DirectX::XMFLOAT3 spritPosition = foods[i]->getPosition();
			spritPosition.y += 3.0f;

			//ワールド座標からスクリーン座標に変換
			DirectX::XMVECTOR ScreenPosition, WorldPosition;
			WorldPosition = DirectX::XMLoadFloat3(&spritPosition);

			ScreenPosition = DirectX::XMVector3Project(
				WorldPosition,
				0.0f, 0.0f,
				screenWidth, screenHeight,
				0.0f, 1.0f,
				Projection,
				View,
				World
			);

			//スクリーン座標
			DirectX::XMFLOAT2 screenPosition;
			DirectX::XMStoreFloat2(&screenPosition, ScreenPosition);

			screenPosition.y += SinPosY();

			//ゲージ描画
			const float grugeWidth = 50.0f;
			const float grugeHeight = 50.0f;

			switch (foods[i]->GetType())
			{
			case foodType::EGG:
				SpriteEgg->Render(rc,
					screenPosition.x - grugeWidth / 2, screenPosition.y,
					0.0f,
					grugeWidth, grugeHeight,
					0.0f,
					1.0f, 1.0f, 1.0f, 1.0f);
				break;
			case foodType::ONION:
				SpriteOnion->Render(rc,
					screenPosition.x - grugeWidth / 2, screenPosition.y,
					0.0f,
					grugeWidth, grugeHeight,
					0.0f,
					1.0f, 1.0f, 1.0f, 1.0f);
				break;
			case foodType::RICE:
				SpriteRice->Render(rc,
					screenPosition.x - grugeWidth / 2, screenPosition.y,
					0.0f,
					grugeWidth, grugeHeight,
					0.0f,
					1.0f, 1.0f, 1.0f, 1.0f);
				break;
			case foodType::TOMATO:
				SpriteTomato->Render(rc,
					screenPosition.x - grugeWidth / 2, screenPosition.y,
					0.0f,
					grugeWidth, grugeHeight,
					0.0f,
					1.0f, 1.0f, 1.0f, 1.0f);
				break;
			case foodType::CHICKENRICE:
				switch (foods[i]->GetOmuType())
				{
				case 0:
					SpriteChikenrice->Render(rc,
						screenPosition.x - grugeWidth / 2, screenPosition.y,
						0.0f,
						grugeWidth, grugeHeight,
						0.0f,
						1.0f, 1.0f, 1.0f, 1.0f);
					break;
				case 1:
					SpriteChikenriceGreen->Render(rc,
						screenPosition.x - grugeWidth / 2, screenPosition.y,
						0.0f,
						grugeWidth, grugeHeight,
						0.0f,
						1.0f, 1.0f, 1.0f, 1.0f);
					break;
				case 2:
					SpriteChikenriceTomato->Render(rc,
						screenPosition.x - grugeWidth / 2, screenPosition.y,
						0.0f,
						grugeWidth, grugeHeight,
						0.0f,
						1.0f, 1.0f, 1.0f, 1.0f);
					break;
				default:
					break;
				}
			default:
				break;
			}

		}
	}
#ifdef DEBUG
	//なんかのポジションを取ってくる
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	//表示場所
	ImGui::SetNextWindowPos(ImVec2(pos.x + 400, pos.y + 400), ImGuiCond_Once);
	//大きさ
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("foodm", nullptr, ImGuiWindowFlags_None))
	{
		//トランスフォーム
		if (ImGui::CollapsingHeader("UIParam", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::DragFloat("frequency", &frequency);
			ImGui::DragFloat("amplitude", &amplitude);
			ImGui::DragFloat("time", &time);
		}
	}
	ImGui::End();

#endif // DEBUG

}

float FoodManager::SinPosY()
{
	return amplitude * sinf(2 * DirectX::XM_PI * frequency * time);
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

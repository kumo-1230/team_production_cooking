#include "StageManager.h"
#include "MapTip/map_manager.h"
#include "Floor.h"
#include "Stove.h"
#include "Pot.h"
#include "Cursor.h"
#include "BaconBox.h"
#include "TileBox.h"
#include "TileNone.h"
#include "Submission.h"
#include <imgui.h>
#include "Sink.h"
#include "CreateDishBox.h"
#include "Board.h"
#include "Collision.h"
#include "Player.h"
#include "EggBox.h"

#define DEBUG

StageManager::StageManager()
{
	Initialize();
}

StageManager::~StageManager()
{
}

void StageManager::Initialize()
{
	floor = std::make_unique<Floor>();
	std::vector<std::vector<int>> map;

	//マップロード
	{
		MapManager mapLoad;
		mapLoad.MapLoad(&mapLoad);
		mapLoad.AllMapSet(map);
	}

	TileMapBank.resize(map.size());
	// 各行ごとに列を初期化（nullptr）
	for (size_t i = 0; i < map.size(); ++i)
	{
		TileMapBank[i].resize(map[i].size()); // 各行に同じ列数を確保
		for (size_t j = 0; j < map[i].size(); ++j)
		{
			TileMapBank[i][j] = nullptr; // 明示的にnullptrで初期化
		}
	}
	for (int i = 0; i < TileMapBank.size(); i++)
	{
		for (int j = 0; j < TileMapBank[i].size();j++)
		{
			DirectX::XMFLOAT3 p = { j * 2.0f,0.0f,i * 2.0f };
			
			switch (map[i][j])
			{
			case TILE_MODEL::NONE:
				TileMapBank[i][j] = std::make_unique<TileNone>(p);
				break;
			case TILE_MODEL::BACON:
				TileMapBank[i][j] = std::make_unique<TileBox>(p);
				tileMapBox.push_back(std::make_unique<BaconBox>(p,map[i][j]));
				break;
			case TILE_MODEL::CABBAGE:
				break;
			case TILE_MODEL::EGG:
				TileMapBank[i][j] = std::make_unique<TileBox>(p);
				tileMapBox.push_back(std::make_unique<EggBox>(p, map[i][j]));
				break;
			case TILE_MODEL::OFFER:
				TileMapBank[i][j] = std::make_unique<Submission>(p,0);
				break;
			case TILE_MODEL::RETURN_DISH:
				TileMapBank[i][j] = std::make_unique<CreateDishBox>(p,0);
				break;
			case TILE_MODEL::ONION:
				break;
			case TILE_MODEL::POTATO:
				break;
			case TILE_MODEL::RICE:
				break;
			case TILE_MODEL::TOMATO:
				break;
			default:
				continue;
				break;
			}
			if (map[i][j] == TILE_MODEL::OFFER || map[i][j] == TILE_MODEL::RETURN_DISH)
			{
				TileMapBank[i][j]->SetMode(map[i][j]);
			}
			else if (map[i][j] != TILE_MODEL::NONE)
			{
				int b = TILE_MODEL::BOX;
				TileMapBank[i][j]->SetMode(b);
			}
			else
			{
				int b = TILE_MODEL::NONE;
				TileMapBank[i][j]->SetMode(b);
			}
		}
	}
	DirectX::XMFLOAT3 p = { 0,0.0f,0.0f };
	cursor = std::make_unique<Cursor>(p);
	key = std::make_unique<KeyInput>();
	sprite = std::make_unique<Sprite>("Data/Sprite/ge-zi.png");

}

void StageManager::SetMapTip()
{
	std::unique_ptr<Utensils> b;
	std::unique_ptr<Utensils> b2;

	bool nextBild = true;
	bool change = true;

	oldX = x;
	oldY = y;
	oldTileMode = TileMode;
	oldLv = Lv;

	int modeBank = TileMapBank[y][x]->GetMode();
	int LvBank = TileMapBank[y][x]->GetLv();
	int LvBank2 = TileMapBank[nextY][nextX]->GetLv();

	DirectX::XMFLOAT3 p = { x * 2.0f,0.0f,y * 2.0f };

	if (modeBank == TILE_MODEL::BOX)
	{
		return;
	}
	if (modeBank == TILE_MODEL::NONE && TileMode == TILE_MODEL::NONE)
	{
		return;
	}
	switch (TileMode)
	{
	case TILE_MODEL::NONE:
		b = std::make_unique<TileNone>(p);
		break;
	case TILE_MODEL::BOARD:
		b = std::make_unique<Board>(p, Lv);
		if (Long)
		{
			if (TileMapBank[nextY][nextX]->GetMode() != TILE_MODEL::BOX)
			{
				p = { nextX * 2.0f,0.0f,nextY * 2.0f };
				b2 = std::make_unique<Board>(p, Lv);
				b->SetFriendOn(Long);
				b->SetFriendX(nextX);
				b->SetFriendY(nextY);

				b2->SetFriendOn(Long);
				b2->SetFriendX(x);
				b2->SetFriendY(y);
			}
			else
			{
				nextBild = false;
			}
		}
		break;
	case TILE_MODEL::POT:
		b = std::make_unique<Pot>(p, Lv);
		if (Long)
		{
			if (TileMapBank[nextY][nextX]->GetMode() != TILE_MODEL::BOX)
			{
				p = { nextX * 2.0f,0.0f,nextY * 2.0f };
				b2 = std::make_unique<Pot>(p, Lv);
				b->SetFriendOn(Long);
				b->SetFriendX(nextX);
				b->SetFriendY(nextY);

				b2->SetFriendOn(Long);
				b2->SetFriendX(x);
				b2->SetFriendY(y);
			}
			else
			{
				nextBild = false;
			}
		}
		break;
	case TILE_MODEL::SINK:
		b = (std::make_unique<Sink>(p, Lv, false));
		p = { nextX * 2.0f,0.0f,nextY * 2.0f };
		b2 = (std::make_unique<Sink>(p, Lv, true));
			break;
	case TILE_MODEL::STOVE:
		b = std::make_unique<Stove>(p,Lv);
		if (Long)
		{
			if (TileMapBank[nextY][nextX]->GetMode() != TILE_MODEL::BOX)
			{
				p = { nextX * 2.0f,0.0f,nextY * 2.0f };
				b2 = std::make_unique<Stove>(p, Lv);
				b->SetFriendOn(Long);
				b->SetFriendX(nextX);
				b->SetFriendY(nextY);

				b2->SetFriendOn(Long);
				b2->SetFriendX(x);
				b2->SetFriendY(y);
			}
			else
			{
				nextBild = false;
			}
		}
		break;
	case TILE_MODEL::TABLE:
		b = std::make_unique<TileNone>(p);
		if (Long)
		{
			if (TileMapBank[nextY][nextX]->GetMode() != TILE_MODEL::BOX)
			{
				p = { nextX * 2.0f,0.0f,nextY * 2.0f };
				b2 = std::make_unique<Stove>(p, Lv);
				b->SetFriendOn(Long);
				b->SetFriendX(nextX);
				b->SetFriendY(nextY);

				b2->SetFriendOn(Long);
				b2->SetFriendX(x);
				b2->SetFriendY(y);
			}
			else
			{
				nextBild = false;
			}
		}
		break;
	default:
		b = std::make_unique<TileNone>(p);
		break;
	}
	if (LvBank >= 1 || LvBank2 >= 1)
	{
		int jage = 0;
		if (TileMapBank[y][x]->GetFriendOn())
		{
			int nx = TileMapBank[y][x]->GetFriendX();
			int ny = TileMapBank[y][x]->GetFriendY();
			DirectX::XMFLOAT3 np = { nx * 2.0f,0.0f,ny * 2.0f };
			TileMapBank[ny][nx] = std::make_unique<TileNone>(np);
			change = false;
			jage++;
		}
		if (TileMapBank[nextY][nextX]->GetFriendOn())
		{
			int nx = TileMapBank[nextY][nextX]->GetFriendX();
			int ny = TileMapBank[nextY][nextX]->GetFriendY();
			DirectX::XMFLOAT3 np = { nx * 2.0f,0.0f,ny * 2.0f };
			TileMapBank[ny][nx] = std::make_unique<TileNone>(np);
			change = false;
			jage++;
		}
		if (jage == 2)
		{
			if (modeBank != TILE_MODEL::NONE)
			{
				if (modeBank != TileMode && TileMode != TILE_MODEL::NONE)
				{
					subtractionMoney -= ADD_MONEY[Lv];
				}
				subtractionMoney += ADD_MONEY[LvBank];
			}
		}
		else if (modeBank != TileMode || Lv != LvBank || Lv != LvBank2)
		{
			if (modeBank != TILE_MODEL::NONE)
			{
				{
					subtractionMoney -= ADD_MONEY[Lv];
				}
				subtractionMoney += ADD_MONEY[LvBank];
			}

		}
	}
	if (nextBild == false)
	{
		TileMapBank[y][x] = std::make_unique<TileNone>(p);
		return;
	}
	if (change)
	{
		{
			if (modeBank != TILE_MODEL::NONE)
			{
				if (modeBank != TileMode && TileMode != TILE_MODEL::NONE || LvBank != Lv && TileMode != TILE_MODEL::NONE)
				{
					subtractionMoney -= ADD_MONEY[Lv];
				}
				else if (modeBank == TileMode && TileMode != TILE_MODEL::NONE || LvBank == Lv && TileMode != TILE_MODEL::NONE)
				{
					subtractionMoney -= ADD_MONEY[Lv];
				}
				subtractionMoney += ADD_MONEY[LvBank];
			}
			else
			{
				subtractionMoney -= ADD_MONEY[Lv];
			}
		}
	}

	TileMapBank[y][x] = nullptr;
	TileMapBank[y][x] = std::move(b);
	TileMapBank[y][x]->SetMode(TileMode);
	if (Long)
	{
		TileMapBank[nextY][nextX] = std::move(b2);
		TileMapBank[nextY][nextX]->SetMode(TileMode);

		TileMapBank[y][x]->SetFriendOn(true);
		TileMapBank[y][x]->SetFriendX(nextX);
		TileMapBank[y][x]->SetFriendY(nextY);

		TileMapBank[nextY][nextX]->SetFriendOn(true);
		TileMapBank[nextY][nextX]->SetFriendX(x);
		TileMapBank[nextY][nextX]->SetFriendY(y);
	}
}

void StageManager::Update(float elapsedTime, DishManager* DM, Player* P,FoodManager* F)
{
	if (build)
	{
		cursor->Update(elapsedTime, x, y);
		if (key->GetKeyDown('E'))
		{
			if (TileMode == 0)
			{
				TileMode = TILE_MODEL::BOARD;
			}
			else
			{
				TileMode++;
			}
			if (TileMode > TILE_MODEL::TABLE)
			{
				TileMode = 0;
			}
		}
		if (key->GetKeyDown('Q'))
		{
			if (TileMode == TILE_MODEL::BOARD)
			{
				TileMode = 0;
			}
			else
			{
				TileMode--;
			}
			if (TileMode < 0)
			{
				TileMode = TILE_MODEL::TABLE;
			}
		}
		if (key->GetKeyDown('1'))
		{
			Lv = 0;
		}
		if (key->GetKeyDown('2'))
		{
			Lv = 1;
		}
		if (key->GetKeyDown('3'))
		{
			Lv = 2;
		}

		if (key->GetKeyDown('R') && Lv != 0)
		{
			if (Long == false)
			{
				Long = true;
			}
			else
			{
				Long = false;

			}
		}
		if (Long == true)
		{
			nextX = x + 1;
			nextY = y;
		}
		else
		{
			nextX = 0;
			nextY = 0;
		}

		if (Lv == 0)
		{
			Long = false;
		}

		if (TileMode == TILE_MODEL::SINK)
		{
			Long = true;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (x != oldX || y != oldY || oldTileMode != TileMode || oldLv != Lv)
			{
				SetMapTip();
			}
		}
	}
	else
	{
		if (key->GetKeyDown('E'))
		{
			for (int i = 0; i < tileMapUtensils.size(); i++)
			{
				if (tileMapUtensils[i]->GetLv() == 0 &&
					Collision::IntersectBoxVsCylinder(
						tileMapUtensils[i]->GetPosition(),
						tileMapUtensils[i]->GetLength(),
						P->GetPosition(),
						P->GetRadius(),
						P->GetHeight()) ||
					tileMapUtensils[i]->GetLv() == 1 ||
					tileMapUtensils[i]->GetLv() == 2)
				{
					switch (tileMapUtensils[i]->GetMode())
					{
					case TILE_MODEL::SINK:
						[[fallthrough]];
					case TILE_MODEL::RETURN_DISH:
						if (tileMapUtensils[i]->GetRight())
						{
							tileMapUtensils[i]->Update(elapsedTime, DM);
						}
						break;
					case TILE_MODEL::OFFER:
						//TODO オーダーどうりの商品が提供されたら
						if (P->getIng() != nullptr)
						{
							F->RemoveFood(P->getIng());
							P->getDish()->setLv(1);
							P->setScore(1000);
							P->SetFood(nullptr);
							P->SetDish(nullptr);
						}
						break;
					default:
						tileMapUtensils[i]->Update(elapsedTime, DM);
						break;
					}
				}
			}
			for (int i = 0; i < tileMapBox.size(); i++)
			{
				if (tileMapBox[i]->GetLv() == 0 &&
					Collision::IntersectBoxVsCylinder(
						tileMapBox[i]->GetPosition(),
						tileMapBox[i]->GetLength(),
						P->GetPosition(),
						P->GetRadius(),
						P->GetHeight()) ||
					tileMapBox[i]->GetLv() == 1 ||
					tileMapBox[i]->GetLv() == 2)
				{
					std::unique_ptr<Ingredients> food;
					switch (tileMapBox[i]->GetMode())
					{
					case TILE_MODEL::BACON:
						food = std::make_unique<Chicken>();
						break;
					case TILE_MODEL::RICE:
						food = std::make_unique<Rice>();
						break;
					case TILE_MODEL::ONION:
						food = std::make_unique<Onion>();
						break;
					case TILE_MODEL::EGG:
						food = std::make_unique<Egg>();
						break;
					default:
						break;
					}
					P->SetFood(food.get());
					F->SetFood(std::move(food));
				}
			}
		}
	}
}

void StageManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	//floor->Render(rc, renderer);
	if (build)
	{
		cursor->Render(rc, renderer);

		for (int i = 0; i < TileMapBank.size(); i++)
		{
			for (int j = 0; j < TileMapBank[i].size(); j++)
			{
				if (TileMapBank[i][j].get() != nullptr)
				{
					TileMapBank[i][j]->Render(rc, renderer);
				}
			}
		}
		for (auto& a : tileMapBox)
		{
			a->Render(rc,renderer);
		}
		for (int i = 0; i < TileMapBank.size(); i++)
		{
			for (int j = 0; j < TileMapBank[i].size(); j++)
			{
				if (TileMapBank[i][j].get() != nullptr)
				{
					if (TileMapBank[i][j]->GetMode() == TILE_MODEL::OFFER)
					{
						int i = 0;
					}
					// スクリーンサイズ取得
					float screenWidth = Graphics::Instance().GetScreenWidth();
					float screenHeight = Graphics::Instance().GetScreenHeight();

					DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&rc.view);
					DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&rc.projection);
					DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();

					//頭上のワールド座標
					DirectX::XMFLOAT3 spritPosition = TileMapBank[i][j]->GetPosition();
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

					//ゲージ描画
					const float grugeWidth = 30.0f;
					const float grugeHeight = 5.0f;

					sprite->Render(rc,
						screenPosition.x - grugeWidth / 2, screenPosition.y,
						0.0f,
						grugeWidth, grugeHeight,
						0.0f,
						1.0f, 1.0f, 1.0f, 1.0f);

				}
			}
		}
	}
	else
	{
		for (const auto& m : tileMapBox)
		{
			m->Render(rc, renderer);
		}
		for (const auto& m : tileMapUtensils)
		{
			m->Render(rc, renderer);
		}
	}
#ifdef DEBUG
	//なんかのポジションを取ってくる
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	//表示場所
	ImGui::SetNextWindowPos(ImVec2(pos.x + 100, pos.y + 100), ImGuiCond_Once);
	//大きさ
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("TileMap", nullptr, ImGuiWindowFlags_None))
	{
		//トランスフォーム
		//if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::InputInt("money", &subtractionMoney);
			ImGui::InputInt("Lv", &Lv);
			ImGui::InputInt("Mode", &TileMode);
			ImGui::Checkbox("Long", &Long);

		}
	}
	ImGui::End();

	if (ImGui::Begin("camera", nullptr, ImGuiWindowFlags_None))
	{
		ImGui::Text("view");
		for (int i = 0; i < 4; i++)
		{
			// 各行をまとめて編集できるようにする
			ImGui::Text("%.3f/ %.3f/ %.3f/ %.3f/",
				rc.view.m[i][0], rc.view.m[i][1], rc.view.m[i][2], rc.view.m[i][3]);
		}
		ImGui::Text("projection");
		for (int i = 0; i < 4; i++)
		{
			// 各行をまとめて編集できるようにする
			ImGui::Text("%.3f/ %.3f/ %.3f/ %.3f/",
				rc.projection.m[i][0], rc.projection.m[i][1], rc.projection.m[i][2], rc.projection.m[i][3]);
		}
	}
	ImGui::End();

#endif // DEBUG


}

void StageManager::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	for (const auto& m : tileMapBox)
	{
		m->RenderDebugPrimitive(rc, renderer);
	}
}

void StageManager::BuildingMap()
{
	tileMapUtensils.clear();
	for (int i = 0; i < TileMapBank.size(); i++)
	{
		for (int j = 0; j < TileMapBank[i].size(); j++)
		{
			DirectX::XMFLOAT3 p = { j * 2.0f,0.0f,i * 2.0f };
			if (TileMapBank[i][j] != nullptr)
			{
				switch (TileMapBank[i][j]->GetMode())
				{
				case TILE_MODEL::NONE:
					break;
				case TILE_MODEL::BOARD:
					tileMapUtensils.push_back(std::make_unique<Board>(p, TileMapBank[i][j]->GetLv()));
					break;
				case TILE_MODEL::POT:
					tileMapUtensils.push_back(std::make_unique<Pot>(p, TileMapBank[i][j]->GetLv()));
					break;
				case TILE_MODEL::SINK:
					tileMapUtensils.push_back(std::make_unique<Stove>(p, TileMapBank[i][j]->GetLv()));
					break;
				case TILE_MODEL::STOVE:
					tileMapUtensils.push_back(std::make_unique<Stove>(p, TileMapBank[i][j]->GetLv()));
					break;
				case TILE_MODEL::TABLE:
					tileMapUtensils.push_back(std::make_unique<Stove>(p, TileMapBank[i][j]->GetLv()));
					break;
				case TILE_MODEL::OFFER:
					tileMapUtensils.push_back(std::make_unique<Submission>(p, TileMapBank[i][j]->GetLv()));
					break;
				case TILE_MODEL::RETURN_DISH:
					tileMapUtensils.push_back(std::make_unique<CreateDishBox>(p, TileMapBank[i][j]->GetLv()));
					break;
				//case TILE_MODEL::BACON:
				//	tileMapBox.push_back(std::make_unique<BaconBox>(p));
				//	break;
				//case TILE_MODEL::STOVE:
				//	tileMapUtensils.push_back(std::make_unique<Stove>(p, TileMapBank[i][j]->GetLv()));
				//	break;
				}
			}
		}
	}
}

#include "StageManager.h"
#include "MapTip/map_manager.h"
#include "Floor.h"
#include "Stove.h"
#include "Pot.h"
#include "Cursor.h"
#include "BaconBox.h"
#include "TileBox.h"
#include "TileNone.h"
#include <imgui.h>

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
				tileMapBox.push_back(std::make_unique<BaconBox>(p));
				break;
			case TILE_MODEL::CABBAGE:
				break;
			case TILE_MODEL::EGG:
				break;
			case TILE_MODEL::OFFER:
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
			if (map[i][j] != TILE_MODEL::NONE)
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
	case TILE_MODEL::FLYER:
		b = std::make_unique<Stove>(p, Lv);
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
	case TILE_MODEL::POT:
		b = std::make_unique<Pot>(p, Lv);
		break;
	case TILE_MODEL::SINK:
		b = std::make_unique<TileNone>(p);
		break;
	case TILE_MODEL::STOVE:
		b = std::make_unique<TileNone>(p);
		break;
	case TILE_MODEL::TABLE:
		b = std::make_unique<TileNone>(p);
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

void StageManager::Update(float elapsedTime)
{
	if (build)
	{
		cursor->Update(elapsedTime, x, y);
		if (key->GetKeyDown('E'))
		{
			if (TileMode == 0)
			{
				TileMode = TILE_MODEL::FLYER;
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
			if (TileMode == TILE_MODEL::FLYER)
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

	}
}

void StageManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	//floor->Render(rc, renderer);
	cursor->Render(rc, renderer);
	if (build)
	{
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
	tileMapBox.clear();
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
				case TILE_MODEL::BACON:
					tileMapBox.push_back(std::make_unique<BaconBox>(p));
					break;
				case TILE_MODEL::STOVE:
					tileMapUtensils.push_back(std::make_unique<Stove>(p, TileMapBank[i][j]->GetLv()));
					break;
				}
			}
		}
	}
}

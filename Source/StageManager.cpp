#include "StageManager.h"
#include "MapTip/map_manager.h"
#include "Floor.h"
#include "Stove.h"
#include "Cursor.h"
#include "BaconBox.h"
#include "TileNone.h"

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
				TileMapBank[i][j] = std::make_unique<BaconBox>(p);
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
			TileMapBank[i][j]->SetMode(map[i][j]);
		}
	}
	DirectX::XMFLOAT3 p = { 0,0.0f,0.0f };
	cursor = std::make_unique<Cursor>(p);
	key = std::make_unique<KeyInput>();
	BuildingMap();
}

void StageManager::SetMapTip()
{
	std::unique_ptr<Stage> b;

	DirectX::XMFLOAT3 p = { x * 2.0f,0.0f,y * 2.0f };

	if (TileMapBank[y][x] != nullptr)
	{
		if (TileMapBank[y][x]->GetMode() <= TILE_MODEL::TOMATO && TileMapBank[y][x]->GetMode() > TILE_MODEL::NONE)
		{
			return;
		}
	}
	TileMapBank[y][x] = nullptr;
	switch (TileMode)
	{
	case TILE_MODEL::NONE:
		b = std::make_unique<TileNone>(p);
		break;
	case TILE_MODEL::FLYER:
		b = std::make_unique<Stove>(p, Lv);
		break;
	case TILE_MODEL::POT:
		b = nullptr;
		break;
	case TILE_MODEL::SINK:
		b = nullptr;
		break;
	case TILE_MODEL::STOVE:
		b = nullptr;
		break;
	case TILE_MODEL::TABLE:
		b = nullptr;
		break;
	default:
		b = nullptr;
		break;
	}

	TileMapBank[y][x] = std::move(b);
	oldX = x;
	oldY = y;
	oldTileMode = TileMode;
	oldLv = Lv;
}

void StageManager::Update(float elapsedTime)
{
	cursor->Update(elapsedTime,x,y);
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
		Lv = 2;
	}
	if (key->GetKeyDown('3'))
	{
		Lv = 3;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (x != oldX || y != oldY || oldTileMode != TileMode || oldLv != Lv)
		{
			SetMapTip();
		}
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
	}
	else
	{
		for (const auto& m : tileMap)
		{
			m->Render(rc, renderer);
		}
	}
}

void StageManager::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	for (const auto& m : tileMap)
	{
		m->RenderDebugPrimitive(rc, renderer);
	}
}

void StageManager::BuildingMap()
{
	tileMap.clear();
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
					tileMap.push_back(std::make_unique<BaconBox>(p));
					break;
				case TILE_MODEL::STOVE:
					tileMap.push_back(std::make_unique<Stove>(p, TileMapBank[i][j]->GetLv()));
					break;
				}
			}
		}
	}
}

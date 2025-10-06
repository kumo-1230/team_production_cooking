#include "StageManager.h"
#include "MapTip/map_manager.h"
#include "Floor.h"
#include "Stove.h"

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
	//マップ情報
	std::vector<std::vector<int>> map;
	//マップロード
	{
		MapManager mapLoad;
		mapLoad.MapLoad(&mapLoad);
		mapLoad.AllMapSet(map);
	}
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			DirectX::XMFLOAT3 p = { i * 2.0f,0.0f,j * 2.0f };

			switch (map[i][j])
			{
			case TILE_MODEL::NONE:
				break;
			case TILE_MODEL::STOVE:
				tileMap.push_back(std::make_unique<Stove>(p));
				break;				
			}
		}
	}
}

void StageManager::Updeate(float elapsedTime)
{
}

void StageManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	//floor->Render(rc, renderer);
	for (const auto& m : tileMap)
	{
		m->Render(rc, renderer);
	}
}

void StageManager::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	for (const auto& m : tileMap)
	{
		m->RenderDebugPrimitive(rc, renderer);
	}
}

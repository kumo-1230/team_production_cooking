#include "map_manager.h"
#include <fstream>

int MapManager::mapStage = 0;
int** MapManager::Cmap = nullptr;

MapManager::~MapManager()
{
	if (map != nullptr) {
		for (int i = 0; i < y; i++) {
			delete[] map[i];
		}
		delete[] map;
	}
}

MapManager::MapManager() :stage(0), save(0), cmapHeight(0)
{

}

const char* MapManager::GetMapFile(int number) { return mapFile[number]; }

void MapManager::MapSave()
{
	std::ofstream out;
	out.open(mapFile[stage], std::ios::binary);
	if (out)
	{
		out.write(reinterpret_cast<const char*>(stage), sizeof(int));
		out.write(reinterpret_cast<const char*>(y),     sizeof(int));
		out.write(reinterpret_cast<const char*>(x),     sizeof(int));

		// マップの本体を書き出し（行単位に）
		for (int i = 0; i < y; ++i)
		{
			out.write(reinterpret_cast<const char*>(map[i]), sizeof(int) * x);
		}

		out.close();
	}

}

void MapManager::MapLoad(MapManager* mp)
{
	std::ifstream in(mp->mapFile[mp->stage], std::ios::binary);
	if (!in) return;

	in.read(reinterpret_cast<char*>(&mp->stage), sizeof(int));
	in.read(reinterpret_cast<char*>(&mp->y), sizeof(int));
	in.read(reinterpret_cast<char*>(&mp->x), sizeof(int));

	mp->SetMap(mp->y, mp->x); // メモリ確保

	for (int i = 0; i < mp->y; ++i)
	{
		in.read(reinterpret_cast<char*>(mp->map[i]), sizeof(int) * mp->x);
	}

	in.close();
}

void MapManager::SetMap(int y,int x)
{
	x = x;
	y = y;
	map = new int*[y];
	for (int i = 0; i < y; i++)
	{
		map[i] = new int[x];
	}

	if (Cmap != nullptr) {
		for (int i = 0; i < cmapHeight; i++) {
			delete[] Cmap[i];
		}
		delete[] Cmap;
	}
	cmapHeight = y;
	Cmap = new int* [y];
	for (int i = 0; i < y; i++) {
		Cmap[i] = new int[x];
	}
}

void MapManager::SetMap(int y, int x, int mapType)
{
	map[y][x] = mapType;
}

void MapManager::AllMapSet(std::vector<std::vector<int>>& Map)
{
	Map.resize(y, std::vector<int>(x));
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			Map[i][j] = map[i][j];
		}
	}
}

void MapManager::CopyMap()
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			Cmap[i][j] = map[i][j];
		}
	}
}

void MapManager::PasteMap()
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			map[i][j] = Cmap[i][j];
		}
	}
}

void MapManager::SetMapInit(int y, int x)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			map[i][j] = 0;
		}
	}
}

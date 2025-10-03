#pragma once
#include <vector>

#define MAX_MAPFILE (1)

class MapManager
{
private:
	int** map;
	static int** Cmap;
	int cmapHeight;
	int save;
	int stage;
	int x,y;
	static int mapStage;
	const char* mapFile[MAX_MAPFILE] =
	{
		"./Data/map/map1.dat"
	};
public:
	MapManager();
	~MapManager();

	void MapSave();

	void MapLoad(MapManager* mp);

	int GetX() { return x; }
	int GetY() { return y; }

	const char* GetMapFile(int number);
	//マップをセットする
	//int	ステージ数
	void SetMap(int y,int x);

	//マップ初期設定
	void SetMapInit(int y, int x);

	//マップ単体セット
	void SetMap(int y, int x, int mapType);

	int** GetMap() { return map; }

	//配列をコピー
	void AllMapSet(std::vector<std::vector<int>>& Map);

	//今のマップをコピー
	void CopyMap();

	//コピーしたマップをペーストする
	void PasteMap();

};
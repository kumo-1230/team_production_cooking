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
	//�}�b�v���Z�b�g����
	//int	�X�e�[�W��
	void SetMap(int y,int x);

	//�}�b�v�����ݒ�
	void SetMapInit(int y, int x);

	//�}�b�v�P�̃Z�b�g
	void SetMap(int y, int x, int mapType);

	int** GetMap() { return map; }

	//�z����R�s�[
	void AllMapSet(std::vector<std::vector<int>>& Map);

	//���̃}�b�v���R�s�[
	void CopyMap();

	//�R�s�[�����}�b�v���y�[�X�g����
	void PasteMap();

};
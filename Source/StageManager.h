#pragma once
#include "stage.h"
#include "Stove.h"
#include "KeyInput.h"

enum TILE_MODEL
{
	NONE = 0,
	BACON,  //�x�[�R��
	CABBAGE,//�L���x�c
	EGG,    //��
	OFFER,  //��
	ONION,  //�ʂ˂�
	POTATO, //�|�e�g
	RICE,   //��
	TOMATO, //�g�}�g

	//�ݒu�\
	FLYER,  //�t���C���[
	POT,    //��
	SINK,   //�V���N
	STOVE,  //�X�g�[�u
	TABLE,  //�e�[�u��
};

class StageManager
{
private:
	//��
	std::unique_ptr<Stage> floor;
	//�^�C���}�b�v
	std::vector<std::unique_ptr<Stage>> tileMap;
	std::vector<std::vector<std::unique_ptr<Stage>>> mapStage;
	std::unique_ptr<Stage> cursor;
	std::unique_ptr<KeyInput> key;
	std::vector<std::vector<std::unique_ptr<Stage>>> TileMapBank;
	int x = 0, y = 0,TileMode = 0,Lv = 0;
	int oldX = -1, oldY = -1,oldTileMode = -1,oldLv = -1;
	bool build = true;

public:
	StageManager();
	~StageManager();

	void Initialize();
public:
	////////////////////////////////////////////

	const Stage* GetFloor() const { return floor.get(); }
	//�w�肵���v�f���̃^�C���}�b�v���擾
	const Stage* GetTileMap(int i) const { return tileMap[i].get(); }

	const int GetTileMapLength() const { return tileMap.size();}

	const DirectX::XMFLOAT3& GetPosition(int i) const { return tileMap[i]->GetPosition(); }

	const DirectX::XMFLOAT3& GetLength(int i) const { return tileMap[i]->GetLength(); }

	//�^�C���}�b�v�ɃZ�b�g����
	void SetMapTip();

	////////////////////////////////////////////

public:

	void Update(float elapsedTime);
	void Render(const RenderContext& rc, ModelRenderer* renderer);
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	void BuildingMap();

};
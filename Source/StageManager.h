#pragma once
#include "stage.h"
#include "Stove.h"

enum TILE_MODEL
{
	NONE = 0,
	STOVE,
};

class StageManager
{
private:
	//��
	std::unique_ptr<Stage> floor;
	//�^�C���}�b�v
	std::vector<std::unique_ptr<Stage>> tileMap;

public:
	StageManager();
	~StageManager();

	void Initialize();
public:
	////////////////////////////////////////////

	const Stage* GetFloor() const { return floor.get(); }
	//�w�肵���v�f���̃^�C���}�b�v���擾
	const Stage* GetTileMap(int i) const { return tileMap[i].get(); }

	const DirectX::XMFLOAT3& GetPosition(int i) const { return tileMap[i]->GetPosition(); }

	const DirectX::XMFLOAT3& GetLength(int i) const { return tileMap[i]->GetLength(); }

	////////////////////////////////////////////

public:

	void Updeate(float elapsedTime);
	void Render(const RenderContext& rc, ModelRenderer* renderer);
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);


};
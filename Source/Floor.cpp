#include "Floor.h"

Floor::Floor()
{
	Initialize();
}

Floor::~Floor()
{
}

void Floor::Initialize()
{
	//ステージモデルを読み込み
	model = std::make_unique<Model>("Data/Model/Stage/ExampleStage.mdl");
	DirectX::XMStoreFloat4x4(&transform, DirectX::XMMatrixIdentity());
}

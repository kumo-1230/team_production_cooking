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
	//�X�e�[�W���f����ǂݍ���
	model = std::make_unique<Model>("Data/Model/Stage/ExampleStage.mdl");
	DirectX::XMStoreFloat4x4(&transform, DirectX::XMMatrixIdentity());
}

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
	model = std::make_unique<Model>("Data/Model/floor/floor.mdl");
	position = { 19,0,9 };
	scale = { 0.1f,0.1f,0.1f };
	UpdateTransform();
	//DirectX::XMStoreFloat4x4(&transform, DirectX::XMMatrixIdentity());
}

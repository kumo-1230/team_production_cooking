#include "BaconBox.h"

BaconBox::BaconBox(DirectX::XMFLOAT3 pos)
{
	position = pos;
	Initialize();
}

BaconBox::~BaconBox()
{
}

void BaconBox::Initialize()
{
	model = std::make_unique<Model>("Data/Model/test1.mdl");
	scale = { 0.1f,0.05f,0.1f };
	UpdateTransform();
}

void BaconBox::Update(float elapsedTime, FoodManager* FM)
{
}

#include "Stove.h"

Stove::Stove(const DirectX::XMFLOAT3& pos,int lv)
{
	Lv = lv;

	position = pos; 
	Initialize();
}

Stove::~Stove()
{
}

void Stove::Initialize()
{
	if (Lv == 0)
	{
		model = std::make_unique<Model>("Data/Model/gasukonro.mdl");
	}
	if (Lv == 1)
	{
		model = std::make_unique<Model>("Data/Model/gasukonroLv2.mdl");
	}
	scale = { 0.1f,0.1f,0.1f };
	UpdateTransform();
}
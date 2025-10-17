#include "Stove.h"

Stove::Stove(const DirectX::XMFLOAT3& pos,int lv, bool Long, bool right)
{
	Lv = lv;

	if (Lv == 0)
	{
		model = std::make_unique<Model>("Data/Model/frypanLv1.mdl");
	}
	if (Long)
	{
		if (right)
		{
			if (Lv == 1)
			{
				model = std::make_unique<Model>("Data/Model/frypanLv2.mdl");
			}
			if (Lv == 2)
			{
				model = std::make_unique<Model>("Data/Model/frypanLv2.mdl");
			}
		}
		else
		{
			if (Lv == 1)
			{
				model = std::make_unique<Model>("Data/Model/frypanLv2.mdl");
			}
			if (Lv == 2)
			{
				model = std::make_unique<Model>("Data/Model/frypanLv2.mdl");
			}
		}
	}
	else
	{
		if (Lv == 1)
		{
			model = std::make_unique<Model>("Data/Model/frypanLv2.mdl");
		}
		if (Lv == 2)
		{
			model = std::make_unique<Model>("Data/Model/frypanLv2.mdl");
		}
	}
	
	position = pos; 
	Initialize();
}

Stove::~Stove()
{
}

void Stove::Initialize()
{
	scale = { 0.1f,0.1f,0.1f };
	UpdateTransform();
}
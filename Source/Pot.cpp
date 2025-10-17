#include "Pot.h"

Pot::Pot(const DirectX::XMFLOAT3& pos, int lv, bool Long, bool right)
{
	Lv = lv;

	if (Lv == 0)
	{
		model = std::make_unique<Model>("Data/Model/PotLv1.mdl");
	}
	if (Long)
	{
		if (right)
		{
			if (Lv == 1)
			{
				model = std::make_unique<Model>("Data/Model/PotLv2L.mdl");
			}
			if (Lv == 2)
			{
				model = std::make_unique<Model>("Data/Model/PotLv3L.mdl");
			}
		}
		else
		{
			if (Lv == 1)
			{
				model = std::make_unique<Model>("Data/Model/PotLv2R.mdl");
			}
			if (Lv == 2)
			{
				model = std::make_unique<Model>("Data/Model/PotLv3R.mdl");
			}
		}
	}
	else
	{
		if (Lv == 1)
		{
			model = std::make_unique<Model>("Data/Model/PotLv2.mdl");
		}
		if (Lv == 2)
		{
			model = std::make_unique<Model>("Data/Model/PotLv3.mdl");
		}
	}

	position = pos;
	Initialize();
}

Pot::~Pot()
{
}

void Pot::Initialize()
{
	scale = { 0.1f,0.1f,0.1f };
	UpdateTransform();
}
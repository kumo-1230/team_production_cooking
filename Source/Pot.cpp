#include "Pot.h"
#include "System/Audio.h"

Pot::Pot(const DirectX::XMFLOAT3& pos, int lv, bool Long, bool right)
{
	Lv = lv;
	if (Lv == 0)
	{
		model = std::make_unique<Model>("Data/Model/Utensils/Pot/PotLv1.mdl");
	}
	if (Long)
	{
		if (right)
		{
			if (Lv == 1)
			{
				model = std::make_unique<Model>("Data/Model/Utensils/Pot/PotLv2L.mdl");
			}
			if (Lv == 2)
			{
				model = std::make_unique<Model>("Data/Model/Utensils/Pot/PotLv3L.mdl");
			}
		}
		else
		{
			if (Lv == 1)
			{
				model = std::make_unique<Model>("Data/Model/Utensils/Pot/PotLv2R.mdl");
			}
			if (Lv == 2)
			{
				model = std::make_unique<Model>("Data/Model/Utensils/Pot/PotLv3R.mdl");
			}
		}
	}
	else
	{
		if (Lv == 1)
		{
			model = std::make_unique<Model>("Data/Model/Utensils/Pot/PotLv2.mdl");
		}
		if (Lv == 2)
		{
			model = std::make_unique<Model>("Data/Model/Utensils/Pot/PotLv3.mdl");
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
	audio = Audio::Instance().LoadAudioSource("Data/Sound/boil.wav");
	scale = { 0.1f,0.1f,0.1f };
	UpdateTransform();
}
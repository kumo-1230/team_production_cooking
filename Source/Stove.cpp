#include "Stove.h"
#include "System/Audio.h"

Stove::Stove(const DirectX::XMFLOAT3& pos,int lv, bool Long, bool right)
{
	Lv = lv;

	if (Lv == 0)
	{
		model = std::make_unique<Model>("Data/Model/Utensils/Storve/stoveLv1.mdl");
	}
	if (Long)
	{
		if (right)
		{
			if (Lv == 1)
			{
				model = std::make_unique<Model>("Data/Model/Utensils/Storve/stoveLv2L.mdl");
			}
			if (Lv == 2)
			{
				model = std::make_unique<Model>("Data/Model/Utensils/Storve/stoveLv3R.mdl");
			}
		}
		else
		{
			if (Lv == 1)
			{
				model = std::make_unique<Model>("Data/Model/Utensils/Storve/stoveLv2R.mdl");
			}
			if (Lv == 2)
			{
				model = std::make_unique<Model>("Data/Model/Utensils/Storve/stoveLv3L.mdl");
			}
		}
	}
	else
	{
		if (Lv == 1)
		{
			model = std::make_unique<Model>("Data/Model/Utensils/Storve/stoveLv2.mdl");
		}
		if (Lv == 2)
		{
			model = std::make_unique<Model>("Data/Model/Utensils/Storve/stoveLv3.mdl");
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
	audio = Audio::Instance().LoadAudioSource("Data/Sound/fire.wav");
	scale = { 0.1f,0.1f,0.1f };
	UpdateTransform();
}
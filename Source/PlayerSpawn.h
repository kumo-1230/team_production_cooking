#pragma once

#include "Box.h"

class PlayerSpown : public  Box
{
public:
	PlayerSpown(DirectX::XMFLOAT3 pos, int m)
	{
		position = pos;
		mode = m;
		Initialize();
	}
	~PlayerSpown() override {}

	//èâä˙âª
	void Initialize()override
	{
		model = std::make_unique<Model>("Data/Model/kyara.mdl");
		scale = { 0.1f,0.1f,0.1f };
		angle = { 0,DirectX::XMConvertToRadians(180),0 };
		length = { 0,0,0 };
		UpdateTransform();
	}
};
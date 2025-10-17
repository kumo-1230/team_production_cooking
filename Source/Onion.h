#pragma once

#include "Box.h"

class OnionBox : public  Box
{
public:
	OnionBox(DirectX::XMFLOAT3 pos, int m)
	{
		position = pos;
		mode = m;
		Initialize();
	}
	~OnionBox() override {}

	//èâä˙âª
	void Initialize()override
	{
		model = std::make_unique<Model>("Data/Model/OnionBox.mdl");
		scale = { 0.1f,0.1f,0.1f };
		angle = { 0,DirectX::XMConvertToRadians(180),0 };
		UpdateTransform();
	}
};
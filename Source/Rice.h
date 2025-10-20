#pragma once

#include "Box.h"

class RiceBox : public  Box
{
public:
	RiceBox(DirectX::XMFLOAT3 pos, int m)
	{
		position = pos;
		mode = m;
		Initialize();
	}
	~RiceBox() override {}

	//èâä˙âª
	void Initialize()override
	{
		model = std::make_unique<Model>("Data/Model/Box/RiceBox.mdl");
		scale = { 0.1f,0.1f,0.1f };
		angle = { 0,DirectX::XMConvertToRadians(180),0 };
		UpdateTransform();
	}
};
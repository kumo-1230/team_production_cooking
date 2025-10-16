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
		model = std::make_unique<Model>("Data/Model/test1.mdl");
		scale = { 0.1f,0.05f,0.1f };
		UpdateTransform();
	}
};
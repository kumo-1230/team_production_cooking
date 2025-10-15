#pragma once

#include "Box.h"

class EggBox : public  Box
{
public:
	EggBox(DirectX::XMFLOAT3 pos, int m)
	{
		position = pos;
		mode = m;
		Initialize();
	}
	~EggBox() override {}

	//èâä˙âª
	void Initialize()override
	{
		model = std::make_unique<Model>("Data/Model/test1.mdl");
		scale = { 0.1f,0.05f,0.1f };
		UpdateTransform();
	}
};
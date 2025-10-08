#pragma once
#include "stage.h"

class TileNone : public Stage
{
public:
	TileNone(DirectX::XMFLOAT3 pos) 
	{
		position = pos;
		model = std::make_unique<Model>("Data/Model/test2.mdl");
		scale = { 0.1f,0.01f,0.1f };
		UpdateTransform();
	};
	~TileNone() {};
};
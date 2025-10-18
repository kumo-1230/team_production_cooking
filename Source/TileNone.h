#pragma once
#include "Utensils.h"

class TileNone : public Utensils
{
public:
	TileNone(DirectX::XMFLOAT3 pos) 
	{
		position = pos;
		model = std::make_unique<Model>("Data/Model/cursor/none.mdl");
		scale = { 0.1f,0.01f,0.1f };
		UpdateTransform();
	};
	~TileNone() {};
};
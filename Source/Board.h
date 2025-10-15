#pragma once
#include "Utensils.h"

class Board : public Utensils
{
public:
	Board(const DirectX::XMFLOAT3& pos, int lv);
	~Board() override;

	//‰Šú‰»
	void Initialize() override;
};
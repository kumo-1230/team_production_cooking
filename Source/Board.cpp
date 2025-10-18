#include "Board.h"

Board::Board(const DirectX::XMFLOAT3& pos, int lv, bool Long, bool right)
{
	Lv = lv;

	if (Lv == 0)
	{
		model = std::make_unique<Model>("Data/Model/Utensils/Board/boardLv1.mdl");
	}
	if (Long)
	{
		if (right)
		{
			if (Lv == 1)
			{
				model = std::make_unique<Model>("Data/Model/Utensils/Board/boardLv2.mdl");
			}
			if (Lv == 2)
			{
				model = std::make_unique<Model>("Data/Model/Utensils/Board/boardLv3.mdl");
			}
		}
		else
		{
			if (Lv == 1)
			{
				model = std::make_unique<Model>("Data/Model/Utensils/Board/boardLv2.mdl");
			}
			if (Lv == 2)
			{
				model = std::make_unique<Model>("Data/Model/Utensils/Board/boardLv3.mdl");
			}
		}
	}
	else
	{
		if (Lv == 1)
		{
			model = std::make_unique<Model>("Data/Model/Utensils/Board/boardLv2.mdl");
		}
		if (Lv == 2)
		{
			model = std::make_unique<Model>("Data/Model/Utensils/Board/boardLv3.mdl");
		}
	}

	position = pos;

	Initialize();
}

Board::~Board()
{
}

void Board::Initialize()
{
	angle = { 0,DirectX::XMConvertToRadians(180),0 };
	scale = { 0.1f,0.1f,0.1f };
	UpdateTransform();
}
#include "Board.h"

Board::Board(const DirectX::XMFLOAT3& pos, int lv)
{
	Lv = lv;
	position = pos;
	Initialize();
}

Board::~Board()
{
}

void Board::Initialize()
{
	model = std::make_unique<Model>("Data/Model/gasukonro.mdl");
	scale = { 0.1f,0.1f,0.1f };
	UpdateTransform();
}
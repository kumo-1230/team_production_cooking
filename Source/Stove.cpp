#include "Stove.h"

Stove::Stove(const DirectX::XMFLOAT3& pos)
{
	Initialize();
	SetPosition(pos);
}

Stove::~Stove()
{
}

void Stove::Initialize()
{
	model = std::make_unique<Model>("Data/Model/test1.mdl");
	scale = { 0.1f,0.1f,0.1f };
}

void Stove::SetPosition(const DirectX::XMFLOAT3& p)
{
	position = p;
	UpdateTransform();
}

void Stove::Updeate(float elapsedTime)
{
}

void Stove::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	Stage::Render(rc, renderer);
}

void Stove::Event()
{
}

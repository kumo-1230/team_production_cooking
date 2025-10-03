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
	model = std::make_unique<Model>("Data/Model/Test.mdl");
	scale = { 0.01f,0.005f,0.01f };
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

#include "Stove.h"

Stove::Stove(const DirectX::XMFLOAT3& pos,int Lv) : Lv(Lv)
{
	position = pos; 
	Initialize();
}

Stove::~Stove()
{
}

void Stove::Initialize()
{
	model = std::make_unique<Model>("Data/Model/test1.mdl");
	scale = { 0.1f,0.1f,0.1f };
	UpdateTransform();
}

void Stove::Update(float elapsedTime)
{
	Utensils::Update(elapsedTime);
}

void Stove::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	Stage::Render(rc, renderer);
}

void Stove::Event()
{
}

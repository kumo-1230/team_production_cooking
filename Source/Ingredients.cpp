#include "Ingredients.h"
#include "ParentChild.h"

Ingredients::Ingredients()
{
	Initialize();
}

Ingredients::~Ingredients()
{

}

void Ingredients::Initialize()
{
	model = std::make_unique<Model>("Data/Model/test1.mdl");
	scale = { 0.1f,0.1f,0.1f };
	ChildOn = true;
	UpdateTransfom();
}

void Ingredients::Finalize()
{

}

void Ingredients::Update(float elapsedTime,const DirectX::XMFLOAT4X4& ParentT)
{
	if (ChildOn == false)
	{
		scale = { 0.1f,0.1f,0.1f };
		UpdateTransfom();
	}
	else
	{
		scale = { 1.0f,1.0f,1.0f };
		UpdateTransfom();
		DirectX::XMFLOAT3 pos = {0,100,50.0f};
		ParentChild::MakeParentAndChild(ParentT,position,scale,angle, transform,pos);
	}

	//モデル行列更新
	model->UpdateTransform();
}

//行列更新処理
void Ingredients::UpdateTransfom()
{
	//スケール行列制作
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	//回転行列を制作
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	//位置行列を作成
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//三つの行列を組み合わせてワールド行列を作成
	DirectX::XMMATRIX W = S * R * T;

	//計算したワールド行列を取り出す
	DirectX::XMStoreFloat4x4(&transform, W);
}

void Ingredients::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
}

void Ingredients::DrawDebugGUI()
{

}

void Ingredients::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{

}

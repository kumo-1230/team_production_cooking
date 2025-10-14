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
	UpdateTransfom();
}
	

void Ingredients::Finalize()
{

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

void Ingredients::setPosition(const DirectX::XMFLOAT3 pos)
{
	this->position = pos;
}

void Ingredients::setScale(const DirectX::XMFLOAT3 scale)
{
	this->scale = scale;
}

void Ingredients::DrawDebugGUI()
{

}

void Ingredients::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{

}

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


//�s��X�V����
void Ingredients::UpdateTransfom()
{
	//�X�P�[���s�񐧍�
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	//��]�s��𐧍�
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	//�ʒu�s����쐬
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//�O�̍s���g�ݍ��킹�ă��[���h�s����쐬
	DirectX::XMMATRIX W = S * R * T;

	//�v�Z�������[���h�s������o��
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

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

	//���f���s��X�V
	model->UpdateTransform();
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

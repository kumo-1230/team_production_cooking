#include "stage.h"

//�R���X�g���N�^
Stage::Stage()
{
}

Stage::~Stage()
{
}

//�|�W�V�����X�V
void Stage::UpdateTransform()
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

//�X�V����
void Stage::Updeate(float elapsedTime)
{

}

//�`�揈��
void Stage::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	//�����_���Ƀ��f����`�悵�Ă��炤
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);
}
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
void Stage::Update(float elapsedTime)
{

}

//�`�揈��
void Stage::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	//�����_���Ƀ��f����`�悵�Ă��炤
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);
}

void Stage::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	using namespace DirectX;
	XMFLOAT3 S = { position.x ,position.y + length.y ,position.z};
	renderer->RenderSphere(rc, position, 0.5f, { 1,1,1,1 });
	renderer->RenderSphere(rc, S, 0.3f, { 1,1,1,1 });
	renderer->RenderBox(rc, S, angle, length, { 1,1,1,1 });
}

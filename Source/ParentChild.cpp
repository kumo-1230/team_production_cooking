#include "ParentChild.h"

void ParentChild::MakeParentAndChild(
	DirectX::XMFLOAT4X4& ParentTransform,
	DirectX::XMFLOAT4X4& ChildTransform)
{
	using namespace DirectX;
	XMMATRIX PW = XMLoadFloat4x4(&ParentTransform);	//�e�̃��[���h���W
	XMMATRIX CG = XMLoadFloat4x4(&ChildTransform);	//�q���̃O���[�o�����W
	XMMATRIX CW = PW * CG;							//�q���̃��[���h���W
	XMStoreFloat4x4(&ChildTransform, CW);			//�K��
}

void ParentChild::MakeParentAndChild(
	DirectX::XMFLOAT4X4& ParentTransform,
	DirectX::XMFLOAT3& ChildPos,
	DirectX::XMFLOAT3& ChildScale,
	DirectX::XMFLOAT3& ChildAngle,
	DirectX::XMFLOAT4X4& ChildTransform,
	DirectX::XMFLOAT3& ApartSize)
{
	using namespace DirectX;
	//����̃��[�J���s����v�Z
	XMMATRIX S = XMMatrixScaling(ChildScale.x,ChildScale.y,ChildScale.z);
	XMMATRIX R = XMMatrixRotationRollPitchYaw(ChildAngle.x, ChildAngle.y, ChildAngle.z);
	XMMATRIX T = XMMatrixTranslation(
		ChildPos.x + ApartSize.x,
		ChildPos.y + ApartSize.y,
		ChildPos.z + ApartSize.z);
	// �e�̃��[���h�s���ǂݍ���
	XMMATRIX PW = XMLoadFloat4x4(&ParentTransform);

	// �q�̍ŏI���[���h�s��i�e�ɃA�^�b�`���ė����j
	XMMATRIX CW = S * R * T * PW;

	XMStoreFloat4x4(&ChildTransform, CW);
}

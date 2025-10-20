#include "ParentChild.h"

void ParentChild::MakeParentAndChild(
	const DirectX::XMFLOAT4X4& ParentTransform,
	DirectX::XMFLOAT4X4& ChildTransform)
{
	using namespace DirectX;
	XMMATRIX PW = XMLoadFloat4x4(&ParentTransform);	//�e�̃��[���h���W
	XMMATRIX CG = XMLoadFloat4x4(&ChildTransform);	//�q���̃O���[�o�����W
	XMMATRIX CW = CG * PW;							//�q���̃��[���h���W
	XMStoreFloat4x4(&ChildTransform, CW);			//�K��
}

void ParentChild::MakeParentAndChild(
	const DirectX::XMFLOAT4X4& ParentTransform,
	const DirectX::XMFLOAT3& ChildPos,
	const DirectX::XMFLOAT3& ChildScale,
	const DirectX::XMFLOAT3& ChildAngle,
	DirectX::XMFLOAT4X4& ChildTransform,
	const DirectX::XMFLOAT3& ApartSize)
{
	using namespace DirectX;
	//����̃��[�J���s����v�Z
	XMMATRIX S = XMMatrixScaling(ChildScale.x,ChildScale.y,ChildScale.z);
	XMMATRIX R = XMMatrixRotationRollPitchYaw(ChildAngle.x, ChildAngle.y, ChildAngle.z);
	//XMMATRIX T = XMMatrixTranslation(
	//	ChildPos.x + ApartSize.x,
	//	ChildPos.y + ApartSize.y,
	//	ChildPos.z + ApartSize.z);
	XMMATRIX T = XMMatrixTranslation(
		ApartSize.x,
		ApartSize.y,
		ApartSize.z);
	// �e�̃��[���h�s���ǂݍ���
	XMMATRIX PW = XMLoadFloat4x4(&ParentTransform);

	// �q�̍ŏI���[���h�s��i�e�ɃA�^�b�`���ė����j
	XMMATRIX CW = S * R * T * PW;

	XMStoreFloat4x4(&ChildTransform, CW);
}

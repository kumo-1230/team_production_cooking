#include "Camera.h"

//�w�����������
void Camera::SetLookAt(const DirectX::XMFLOAT3& eye, const DirectX::XMFLOAT3& focus, const DirectX::XMFLOAT3& up)
{
	//���_�A�����_�A������`�r���[�s�񐧍�
	DirectX::XMVECTOR Eye   = DirectX::XMLoadFloat3(&eye);
	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	DirectX::XMVECTOR Up    = DirectX::XMLoadFloat3(&up);
	DirectX::XMMATRIX View  = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
	DirectX::XMStoreFloat4x4(&view, View);

	//�J�������������o��
	this->right.x = GetView()._11;
	this->right.y = GetView()._21;
	this->right.z = GetView()._31;

	this->up.x    = GetView()._12;
	this->up.y    = GetView()._22;
	this->up.z    = GetView()._32;

	this->front.x = GetView()._13;
	this->front.y = GetView()._23;
	this->front.z = GetView()._33;

	//���_�A�����_��ۑ�
	this->eye     = eye;
	this->focus   = focus;
}

//�p�[�X�y�N�e�B�u�ݒ�
void Camera::SetPerspectibeFov(float fovY, float aspect, float nearZ, float farZ)
{
	//��p,��ʔ䗦�A�N���b�v��������v���W�F�N�V�����s��쐬
	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY,aspect,nearZ,farZ);

	DirectX::XMStoreFloat4x4(&projection, Projection);
}
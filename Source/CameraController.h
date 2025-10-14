#pragma once
#include <DirectXMath.h>
#include "Camera.h"
#define CAMERA_HEIGHT 35
#define CAMERA_X 15
#define CAMERA_Z -15
//#define CAMERA_HEIGHT 35
//#define CAMERA_X 0
//#define CAMERA_Z 0

class CameraController
{
private:
	DirectX::XMFLOAT3	target    = { 0,0,0 };//�����_
	DirectX::XMFLOAT3	angle     = { 0,0,0 };//��]�p�x
	float				rollSpeed = DirectX::XMConvertToRadians(45);//��]���x
	float				range     = 10.0f;//����
	float				maxAngleX = DirectX::XMConvertToRadians(45);
	float				minAngleX = DirectX::XMConvertToRadians(-45);
public:
	//�X�V����
	void Updeate(float elapsedTime, Camera* camera);

	//�^�[�Q�b�g�ʒu
	void SetTarget(const DirectX::XMFLOAT3& target) { this->target = target; }
};
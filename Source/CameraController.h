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
	DirectX::XMFLOAT3	target    = { 0,0,0 };//注視点
	DirectX::XMFLOAT3	angle     = { 0,0,0 };//回転角度
	float				rollSpeed = DirectX::XMConvertToRadians(45);//回転速度
	float				range     = 10.0f;//距離
	float				maxAngleX = DirectX::XMConvertToRadians(45);
	float				minAngleX = DirectX::XMConvertToRadians(-45);
public:
	//更新処理
	void Updeate(float elapsedTime, Camera* camera);

	//ターゲット位置
	void SetTarget(const DirectX::XMFLOAT3& target) { this->target = target; }
};
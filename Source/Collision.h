#pragma once

#include <DirectXMath.h>

//�R���W����
class Collision
{
public:
	//���Ƌ��̌�������(�~�����m)
	static bool IntersectSphereVsSphere(
		const DirectX::XMFLOAT3& positionA,
		float radiusA,
		const DirectX::XMFLOAT3& positionB,
		float radiusB,
		DirectX::XMFLOAT3& outPositionB
	);
	//�~�����m�̌�������
	static bool IntersectCylinderVsCylinder(
		const DirectX::XMFLOAT3& positionA,
		float radiusA,
		float heightA,
		const DirectX::XMFLOAT3& positionB,
		float radiusB,
		float heightB,
		DirectX::XMFLOAT3& outPositionB
	);
	//�~�����m�̌�������
	static bool IntersectCylinderVsCylinder(
		const DirectX::XMFLOAT3& positionA,
		float radiusA,
		float heightA,
		const DirectX::XMFLOAT3& positionB,
		float radiusB,
		float heightB
	);

	//���Ɖ~���̌�������
	static bool IntersectSphereVsCylinder(
		const DirectX::XMFLOAT3& sphereP,
		float sphereR,
		const DirectX::XMFLOAT3& cylinderP,
		float cylinderR,
		float cylinderH,
		DirectX::XMFLOAT3& outCylinderP
	);

	//���Ɖ~���̌�������
	static bool IntersectSphereVsCylinder(
		const DirectX::XMFLOAT3& sphereP,
		float sphereR,
		const DirectX::XMFLOAT3& cylinderP,
		float cylinderR,
		float cylinderH
	);
};
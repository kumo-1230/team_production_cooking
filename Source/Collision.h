#pragma once

#include <DirectXMath.h>
#include "System/Graphics.h"


//�R���W����
class Collision
{
private:
	int takahata = 0;
	int hatarannbu;

	static DirectX::XMFLOAT3& DefaultFloat3()
	{
		static DirectX::XMFLOAT3 defaultP = { 0.0f,0.0f,0.0f };
		return defaultP;
	}
public:
	//���Ƌ��̌�������(�~�����m)
	static bool IntersectSphereVsSphere(
		const DirectX::XMFLOAT3& positionA,
		float radiusA,
		const DirectX::XMFLOAT3& positionB,
		float radiusB,
		DirectX::XMFLOAT3& outPositionB = DefaultFloat3()
	);
	//�~�����m�̌�������
	static bool IntersectCylinderVsCylinder(
		const DirectX::XMFLOAT3& positionA,
		float radiusA,
		float heightA,
		const DirectX::XMFLOAT3& positionB,
		float radiusB,
		float heightB,
		DirectX::XMFLOAT3& outPositionB = DefaultFloat3()
	);

	//���Ɖ~���̌�������
	static bool IntersectSphereVsCylinder(
		const DirectX::XMFLOAT3& sphereP,
		float sphereR,
		const DirectX::XMFLOAT3& cylinderP,
		float cylinderR,
		float cylinderH,
		DirectX::XMFLOAT3& outCylinderP = DefaultFloat3()
	);

	//�l�p�Ǝl�p
	static bool IntersectBoxVsBox(
		const DirectX::XMFLOAT3& posA,
		const DirectX::XMFLOAT3& lengthA,
		const DirectX::XMFLOAT3& posB,
		const DirectX::XMFLOAT3& lengthB,
		DirectX::XMFLOAT3& outPosition = DefaultFloat3()
	);

	//�l�p�Ɖ~��
	static bool IntersectBoxVsCylinder(
		const DirectX::XMFLOAT3& posA,
		const DirectX::XMFLOAT3& lengthA,
		const DirectX::XMFLOAT3& cylinderP,
		float cylinderR,
		float cylinderH,
		DirectX::XMFLOAT3& outPosition = DefaultFloat3()
	);
};
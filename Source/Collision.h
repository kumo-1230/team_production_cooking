#pragma once

#include <DirectXMath.h>

//ƒRƒŠƒWƒ‡ƒ“
class Collision
{
public:
	//‹…‚Æ‹…‚ÌŒğ·”»’è(‰~’Œ“¯m)
	static bool IntersectSphereVsSphere(
		const DirectX::XMFLOAT3& positionA,
		float radiusA,
		const DirectX::XMFLOAT3& positionB,
		float radiusB,
		DirectX::XMFLOAT3& outPositionB
	);
	//‰~’Œ“¯m‚ÌŒğ·”»’è
	static bool IntersectCylinderVsCylinder(
		const DirectX::XMFLOAT3& positionA,
		float radiusA,
		float heightA,
		const DirectX::XMFLOAT3& positionB,
		float radiusB,
		float heightB,
		DirectX::XMFLOAT3& outPositionB
	);
	//‰~’Œ“¯m‚ÌŒğ·”»’è
	static bool IntersectCylinderVsCylinder(
		const DirectX::XMFLOAT3& positionA,
		float radiusA,
		float heightA,
		const DirectX::XMFLOAT3& positionB,
		float radiusB,
		float heightB
	);

	//‹…‚Æ‰~’Œ‚ÌŒğ·”»’è
	static bool IntersectSphereVsCylinder(
		const DirectX::XMFLOAT3& sphereP,
		float sphereR,
		const DirectX::XMFLOAT3& cylinderP,
		float cylinderR,
		float cylinderH,
		DirectX::XMFLOAT3& outCylinderP
	);

	//‹…‚Æ‰~’Œ‚ÌŒğ·”»’è
	static bool IntersectSphereVsCylinder(
		const DirectX::XMFLOAT3& sphereP,
		float sphereR,
		const DirectX::XMFLOAT3& cylinderP,
		float cylinderR,
		float cylinderH
	);
};
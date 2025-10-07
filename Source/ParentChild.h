#pragma once

#include <DirectXMath.h>

class ParentChild
{
public:
	static void MakeParentAndChild(
		DirectX::XMFLOAT4X4& ParentTransform,
		DirectX::XMFLOAT4X4& ChildTransform
	);

	static void MakeParentAndChild(
		DirectX::XMFLOAT4X4& ParentTransform,
		DirectX::XMFLOAT3& ChildPos,
		DirectX::XMFLOAT3& ChildScale,
		DirectX::XMFLOAT3& ChildAngle,
		DirectX::XMFLOAT4X4& ChildTransform,
		DirectX::XMFLOAT3& ApartSize
	);
};
#include "Collision.h"

//球同士の当たり判定
bool Collision::IntersectSphereVsSphere(
	const DirectX::XMFLOAT3& positionA,
	float radiusA,
	const DirectX::XMFLOAT3& positionB,
	float radiusB,
	DirectX::XMFLOAT3& outPositionB)
{
	{
		//A->Bの単位ベクトルを算出
		//型変換
		DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat3(&positionA);
		DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat3(&positionB);
		//ベクトルを求める
		DirectX::XMVECTOR Vec		= DirectX::XMVectorSubtract(PositionB, PositionA);
		//長さを求める
		DirectX::XMVECTOR LengthSq	= DirectX::XMVector3Length(Vec);
		float lengthSq;
		//アドレスを入れる
		DirectX::XMStoreFloat(&lengthSq, LengthSq);

		//距離判定
		float range = radiusA + radiusB;
		if (range < lengthSq)
		{
			return false;
		}

		//正規化
		DirectX::XMVECTOR outB = DirectX::XMVector3Normalize(Vec);
		//押し出す距離
		outB = DirectX::XMVectorScale(outB, range);
		//押し出す場所
		outB = DirectX::XMVectorAdd(PositionA, outB);
		//押し出す
		DirectX::XMStoreFloat3(&outPositionB, outB);

		return true;
	}

}

//円柱同士の当たり判定
bool Collision::IntersectCylinderVsCylinder(const DirectX::XMFLOAT3& positionA, float radiusA, float heightA, const DirectX::XMFLOAT3& positionB, float radiusB, float heightB, DirectX::XMFLOAT3& outPositionB)
{
	//Aの足元がBの頭より上なら当たっていない
	if (positionA.y > positionB.y + heightB)
	{
		return false;
	}

	//Aの頭がBの足元よりしたなら当たっていない
	if (positionA.y + heightA < positionB.y)
	{
		return false;
	}

	//XZ平面での範囲チェック
	float vx = positionB.x - positionA.x;
	float vz = positionB.z - positionA.z;
	float range = radiusA + radiusB;
	float dist = vx * vx + vz * vz;
	if (dist > range * range)
	{
		return false;
	}

	//単位ベクトル化
	dist = sqrtf(dist);
	vx /= dist;
	vz /= dist;
	float push = range - dist;

	//AがBを押し出す
	outPositionB.x = positionB.x + vx * push;
	outPositionB.y = positionB.y;
	outPositionB.z = positionB.z + vz * push;

	return true;
}

//円柱同士の当たり判定
bool Collision::IntersectCylinderVsCylinder(const DirectX::XMFLOAT3& positionA, float radiusA, float heightA, const DirectX::XMFLOAT3& positionB, float radiusB, float heightB)
{
	//Aの足元がBの頭より上なら当たっていない
	if (positionA.y > positionB.y + heightB)
	{
		return false;
	}

	//Aの頭がBの足元よりしたなら当たっていない
	if (positionA.y + heightA < positionB.y)
	{
		return false;
	}

	//XZ平面での範囲チェック
	float vx = positionB.x - positionA.x;
	float vz = positionB.z - positionA.z;
	float range = radiusA + radiusB;
	float dist = vx * vx + vz * vz;
	if (dist > range * range)
	{
		return false;
	}

	//単位ベクトル化
	dist = sqrtf(dist);
	vx /= dist;
	vz /= dist;
	float push = range - dist;

	return true;
}

//球と円柱の交差判定
bool Collision::IntersectSphereVsCylinder(const DirectX::XMFLOAT3& sphereP, float sphereR, const DirectX::XMFLOAT3& cylinderP, float cylinderR, float cylinderH, DirectX::XMFLOAT3& outCylinderP)
{
	//Aの足元がBの頭より上なら当たっていない
	if (sphereP.y > cylinderP.y + cylinderH)
	{
		return false;
	}

	//Aの頭がBの足元よりしたなら当たっていない
	if (sphereP.y + sphereR < cylinderP.y)
	{
		return false;
	}

	//XZ平面での範囲チェック
	float vx = cylinderP.x - sphereP.x;
	float vz = cylinderP.z - sphereP.z;
	float range = sphereR + cylinderR;
	float dist = vx * vx + vz * vz;
	if (dist > range * range)
	{
		return false;
	}

	//単位ベクトル化
	dist = sqrtf(dist);
	vx /= dist;
	vz /= dist;
	float push = range - dist;

	//AがBを押し出す
	outCylinderP.x = cylinderP.x + vx * push;
	outCylinderP.y = cylinderP.y;
	outCylinderP.z = cylinderP.z + vz * push;

	return true;
}

//球と円柱の当たり判定(out無し)
bool Collision::IntersectSphereVsCylinder(const DirectX::XMFLOAT3& sphereP, float sphereR, const DirectX::XMFLOAT3& cylinderP, float cylinderR, float cylinderH)
{
	//Aの足元がBの頭より上なら当たっていない
	if (sphereP.y > cylinderP.y + cylinderH)
	{
		return false;
	}

	//Aの頭がBの足元よりしたなら当たっていない
	if (sphereP.y + sphereR < cylinderP.y)
	{
		return false;
	}

	//XZ平面での範囲チェック
	float vx = cylinderP.x - sphereP.x;
	float vz = cylinderP.z - sphereP.z;
	float range = sphereR + cylinderR;
	float dist = vx * vx + vz * vz;
	if (dist > range * range)
	{
		return false;
	}

	//単位ベクトル化
	dist = sqrtf(dist);
	vx /= dist;
	vz /= dist;
	float push = range - dist;

	return true;
}

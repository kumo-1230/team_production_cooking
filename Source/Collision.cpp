#include "Collision.h"

//�����m�̓����蔻��
bool Collision::IntersectSphereVsSphere(
	const DirectX::XMFLOAT3& positionA,
	float radiusA,
	const DirectX::XMFLOAT3& positionB,
	float radiusB,
	DirectX::XMFLOAT3& outPositionB)
{
	{
		//A->B�̒P�ʃx�N�g�����Z�o
		//�^�ϊ�
		DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat3(&positionA);
		DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat3(&positionB);
		//�x�N�g�������߂�
		DirectX::XMVECTOR Vec		= DirectX::XMVectorSubtract(PositionB, PositionA);
		//���������߂�
		DirectX::XMVECTOR LengthSq	= DirectX::XMVector3Length(Vec);
		float lengthSq;
		//�A�h���X������
		DirectX::XMStoreFloat(&lengthSq, LengthSq);

		//��������
		float range = radiusA + radiusB;
		if (range < lengthSq)
		{
			return false;
		}

		//���K��
		DirectX::XMVECTOR outB = DirectX::XMVector3Normalize(Vec);
		//�����o������
		outB = DirectX::XMVectorScale(outB, range);
		//�����o���ꏊ
		outB = DirectX::XMVectorAdd(PositionA, outB);
		//�����o��
		DirectX::XMStoreFloat3(&outPositionB, outB);

		return true;
	}

}

//�~�����m�̓����蔻��
bool Collision::IntersectCylinderVsCylinder(const DirectX::XMFLOAT3& positionA, float radiusA, float heightA, const DirectX::XMFLOAT3& positionB, float radiusB, float heightB, DirectX::XMFLOAT3& outPositionB)
{
	//A�̑�����B�̓�����Ȃ瓖�����Ă��Ȃ�
	if (positionA.y > positionB.y + heightB)
	{
		return false;
	}

	//A�̓���B�̑�����肵���Ȃ瓖�����Ă��Ȃ�
	if (positionA.y + heightA < positionB.y)
	{
		return false;
	}

	//XZ���ʂł͈̔̓`�F�b�N
	float vx = positionB.x - positionA.x;
	float vz = positionB.z - positionA.z;
	float range = radiusA + radiusB;
	float dist = vx * vx + vz * vz;
	if (dist > range * range)
	{
		return false;
	}

	//�P�ʃx�N�g����
	dist = sqrtf(dist);
	vx /= dist;
	vz /= dist;
	float push = range - dist;

	//A��B�������o��
	outPositionB.x = positionB.x + vx * push;
	outPositionB.y = positionB.y;
	outPositionB.z = positionB.z + vz * push;

	return true;
}

//�~�����m�̓����蔻��
bool Collision::IntersectCylinderVsCylinder(const DirectX::XMFLOAT3& positionA, float radiusA, float heightA, const DirectX::XMFLOAT3& positionB, float radiusB, float heightB)
{
	//A�̑�����B�̓�����Ȃ瓖�����Ă��Ȃ�
	if (positionA.y > positionB.y + heightB)
	{
		return false;
	}

	//A�̓���B�̑�����肵���Ȃ瓖�����Ă��Ȃ�
	if (positionA.y + heightA < positionB.y)
	{
		return false;
	}

	//XZ���ʂł͈̔̓`�F�b�N
	float vx = positionB.x - positionA.x;
	float vz = positionB.z - positionA.z;
	float range = radiusA + radiusB;
	float dist = vx * vx + vz * vz;
	if (dist > range * range)
	{
		return false;
	}

	//�P�ʃx�N�g����
	dist = sqrtf(dist);
	vx /= dist;
	vz /= dist;
	float push = range - dist;

	return true;
}

//���Ɖ~���̌�������
bool Collision::IntersectSphereVsCylinder(const DirectX::XMFLOAT3& sphereP, float sphereR, const DirectX::XMFLOAT3& cylinderP, float cylinderR, float cylinderH, DirectX::XMFLOAT3& outCylinderP)
{
	//A�̑�����B�̓�����Ȃ瓖�����Ă��Ȃ�
	if (sphereP.y > cylinderP.y + cylinderH)
	{
		return false;
	}

	//A�̓���B�̑�����肵���Ȃ瓖�����Ă��Ȃ�
	if (sphereP.y + sphereR < cylinderP.y)
	{
		return false;
	}

	//XZ���ʂł͈̔̓`�F�b�N
	float vx = cylinderP.x - sphereP.x;
	float vz = cylinderP.z - sphereP.z;
	float range = sphereR + cylinderR;
	float dist = vx * vx + vz * vz;
	if (dist > range * range)
	{
		return false;
	}

	//�P�ʃx�N�g����
	dist = sqrtf(dist);
	vx /= dist;
	vz /= dist;
	float push = range - dist;

	//A��B�������o��
	outCylinderP.x = cylinderP.x + vx * push;
	outCylinderP.y = cylinderP.y;
	outCylinderP.z = cylinderP.z + vz * push;

	return true;
}

//���Ɖ~���̓����蔻��(out����)
bool Collision::IntersectSphereVsCylinder(const DirectX::XMFLOAT3& sphereP, float sphereR, const DirectX::XMFLOAT3& cylinderP, float cylinderR, float cylinderH)
{
	//A�̑�����B�̓�����Ȃ瓖�����Ă��Ȃ�
	if (sphereP.y > cylinderP.y + cylinderH)
	{
		return false;
	}

	//A�̓���B�̑�����肵���Ȃ瓖�����Ă��Ȃ�
	if (sphereP.y + sphereR < cylinderP.y)
	{
		return false;
	}

	//XZ���ʂł͈̔̓`�F�b�N
	float vx = cylinderP.x - sphereP.x;
	float vz = cylinderP.z - sphereP.z;
	float range = sphereR + cylinderR;
	float dist = vx * vx + vz * vz;
	if (dist > range * range)
	{
		return false;
	}

	//�P�ʃx�N�g����
	dist = sqrtf(dist);
	vx /= dist;
	vz /= dist;
	float push = range - dist;

	return true;
}

#include "Collision.h"
#include <algorithm>

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
bool Collision::IntersectCylinderVsCylinder(const DirectX::XMFLOAT3& positionA,
	float radiusA,
	float heightA,
	const DirectX::XMFLOAT3& positionB,
	float radiusB,
	float heightB,
	DirectX::XMFLOAT3& outPositionB)
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

//���Ɖ~���̌�������
bool Collision::IntersectSphereVsCylinder(
	const DirectX::XMFLOAT3& sphereP,
	float sphereR,
	const DirectX::XMFLOAT3& cylinderP,
	float cylinderR,
	float cylinderH,
	DirectX::XMFLOAT3& outCylinderP)
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

//�l�p�Ǝl�p�̓����蔻��
bool Collision::IntersectBoxVsBox(
	const DirectX::XMFLOAT3& posA,
	const DirectX::XMFLOAT3& lengthA,
	const DirectX::XMFLOAT3& posB,
	const DirectX::XMFLOAT3& lengthB,
	DirectX::XMFLOAT3& outPosition)
{
	DirectX::XMFLOAT3 StartPosA;
	DirectX::XMFLOAT3 StartPosB;

	StartPosA.x = posA.x - (lengthA.x * 0.5f);
	StartPosA.z = posA.z - (lengthA.z * 0.5f);
	StartPosA.y = posA.y;

	StartPosB.x = posB.x - (lengthB.x * 0.5f);
	StartPosB.z = posB.z - (lengthB.z * 0.5f);
	StartPosB.y = posB.y;

	return !(StartPosA.x + lengthA.x < StartPosB.x || //B��A�̊O�ɂ��邩
			 StartPosB.x + lengthB.x < StartPosA.x || //A��B�̊O�ɂ��邩
			 StartPosA.y + lengthA.y < StartPosB.y || //B��A�̊O�ɂ��邩
			 StartPosB.y + lengthB.y < StartPosA.y || //A��B�̊O�ɂ��邩
			 StartPosA.z + lengthA.z < StartPosB.z || //B��A�̊O�ɂ��邩
			 StartPosB.z + lengthB.z < StartPosA.z	  //A��B�̊O�ɂ��邩
			);
}

//�l�p�Ɖ~���̓����蔻��
bool Collision::IntersectBoxVsCylinder(
	const DirectX::XMFLOAT3& posA,
	const DirectX::XMFLOAT3& lengthA,
	const DirectX::XMFLOAT3& cylinderP,
	float cylinderR,
	float cylinderH,
	DirectX::XMFLOAT3& outPosition)
{

	if (posA.y + lengthA.y < cylinderP.y) return false;
	if (cylinderP.y + cylinderH < posA.y) return false;

	{
		//�l�p�̎n�܂肩��I���̏ꏊ�܂�
		float boxMinX = posA.x - lengthA.x * 0.5f;
		float boxMaxX = posA.x + lengthA.x * 0.5f;
		float boxMinZ = posA.z - lengthA.z * 0.5f;
		float boxMaxZ = posA.z + lengthA.z * 0.5f;

		//�~�̒��S����l�p�̍ŋߐړ_�����߂�
		float closestX = std::max(boxMinX, std::min(cylinderP.x, boxMaxX));
		float closestZ = std::max(boxMinZ, std::min(cylinderP.z, boxMaxZ));

		//�~�̒��S����l�p�̍Őڋߓ_�܂ł̋���������
		float dx = cylinderP.x - closestX;
		float dz = cylinderP.z - closestZ;

		//�~�Ǝl�p�`�̋��������a���Ȃ�Փ�
		if ((dx * dx + dz * dz) <= (cylinderR * cylinderR))
		{
			float vx = cylinderP.x - posA.x;
			float vz = cylinderP.z - posA.z;
			float dist = vx * vx + vz * vz;
			dist = sqrtf(dist);
			vx /= dist;
			vz /= dist;
			float push = dist - cylinderR;

			outPosition.x = posA.x + vx * push;
			outPosition.y = posA.y;
			outPosition.z = posA.z + vz * push;

			return true;
		}
		return false;
	}

}

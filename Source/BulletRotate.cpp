#include "BulletRotate.h"
#include "Player.h"
#include "EnemyManager.h"

BulletRotate::BulletRotate(int Lv) :Weapon(WEAPON::ROTATION)
{
	model.reset(new Model("Data/Model/Sword/Sword.mdl"));

	//�X�P�[�����O
	scale.x = scale.y = scale.z = 3.0f;
	switch (Lv)
	{
	case 1:
		InitializeLv1();
		break;
	case 2:
		InitializeLv2();
		break;
	case 3:
		InitializeLv3();
		break;
	case 4:
		InitializeLv4();
		break;
	case 5:
		InitializeLv5();
		break;
	}
	coolTimeBank = coolTime;
	lifeTimerBank = lifeTimer;
}

BulletRotate::~BulletRotate()
{
}

void BulletRotate::InitializeLv1()
{
	lifeTimer = 3.0f;
	coolTime = 1.0f;
	turnSpeed = DirectX::XMConvertToRadians(180);
}

void BulletRotate::InitializeLv2()
{
	lifeTimer = 3.5f;
	coolTime = 0.8f;
	turnSpeed = DirectX::XMConvertToRadians(200);
}

void BulletRotate::InitializeLv3()
{
	lifeTimer = 4.0f;
	coolTime = 0.6f;
	turnSpeed = DirectX::XMConvertToRadians(220);
}

void BulletRotate::InitializeLv4()
{
	lifeTimer = 4.5f;
	coolTime = 0.4f;
	turnSpeed = DirectX::XMConvertToRadians(240);
}

void BulletRotate::InitializeLv5()
{
	lifeTimer = 5.0f;
	coolTime = 0.2f;
	turnSpeed = DirectX::XMConvertToRadians(260);
}

void BulletRotate::Update(float elapsedTime, const DirectX::XMFLOAT3& pos)
{
	//�����X�V
	lifeTimer -= 1 * elapsedTime;
	if (lifeTimer < 0)
	{
		//�����폜
		Destroy();
	}

	using namespace DirectX;

	CPos = pos;

	// ��苗���̏����I�t�Z�b�g�iX����5���ꂽ�ʒu�j
	XMVECTOR Offset = XMLoadFloat3(&offset);

	// ��]�p�x�i���Ԃɉ����ĕω�������Ƃ��邮����j
	angle += turnSpeed * elapsedTime;

	// Y����]�̃N�H�[�^�j�I�����쐬
	XMVECTOR q = XMQuaternionRotationAxis(XMVectorSet(0, 1, 0, 0), angle);

	// �N�H�[�^�j�I���ŃI�t�Z�b�g����]
	XMVECTOR rotatedOffset = XMVector3Rotate(Offset, q);

	// �ŏI���W = ���S + ��]��I�t�Z�b�g
	XMVECTOR target = XMVectorAdd(XMLoadFloat3(&CPos), rotatedOffset);

	XMStoreFloat3(&position, target);	//�I�u�W�F�N�g�s����X�V
	UpdateTransform();

	//���f���s��X�V
	model->UpdateTransform();
}

void BulletRotate::Launch(const Player& p, const EnemyManager& em, const Enemy& e, int lanchChar)
{
	if (lanchChar == LCHAR::PLAYER)
	{
		//���ˈʒu(��������)
		position.x = p.GetPosition().x;
		position.y = p.GetPosition().y + p.GetHeight() * 0.5f;
		position.z = p.GetPosition().z;
	}
	else if (lanchChar == LCHAR::ENEMY)
	{
		//���ˈʒu(��������)
		position.x = e.GetPosition().x;
		position.y = e.GetPosition().y + e.GetHeight() * 0.5f;
		position.z = e.GetPosition().z;
	}

	lifeTimer = lifeTimerBank;
	coolTime = coolTimeBank;

	UpdateTransform();
}
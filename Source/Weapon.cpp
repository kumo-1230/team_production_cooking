#include "Weapon.h"
#include "Player.h"
#include "EnemyManager.h"

Weapon::Weapon(int mode)
{
	weaponMode = mode;
}

void Weapon::Update(float elapsedTime)
{
}

void Weapon::Update(float elapsedTime, const DirectX::XMFLOAT3& pos)
{
}

void Weapon::Render(const RenderContext& rc, ModelRenderer* mr)
{
	mr->Render(rc, transform, model.get(), ShaderId::Lambert);
}

void Weapon::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
}

void Weapon::Destroy()
{
	invisibule = true;
}

void Weapon::CoolTimeDown(float elapsedTime)
{
	coolTime -= 1 * elapsedTime;
}

void Weapon::Launch(const Player& p, const EnemyManager& em, const Enemy& e, int lanchChar)
{
}

void Weapon::UpdateTransform()
{
	DirectX::XMVECTOR Front, Up, Right;

	//前ベクトル
	Front = DirectX::XMLoadFloat3(&direction);
	Front = DirectX::XMVector3Normalize(Front);

	//仮の上ベクトルを算出
	Up = DirectX::XMVectorSet(0.001f, 1, 0, 0);
	Up = DirectX::XMVector3Normalize(Up);

	//右ベクトルを算出
	Right = DirectX::XMVector3Cross(Front, Up);
	Right = DirectX::XMVector3Normalize(Right);

	//上ベクトルを算出
	Up = DirectX::XMVector3Cross(Front, Right);
	Up = DirectX::XMVector3Normalize(Up);

	//計算結果を取り出し
	DirectX::XMFLOAT3 right, up, front;
	DirectX::XMStoreFloat3(&right, Right);
	DirectX::XMStoreFloat3(&up, Up);
	DirectX::XMStoreFloat3(&front, Front);

	transform._11 = right.x * scale.x;
	transform._12 = right.y * scale.x;
	transform._13 = right.z * scale.x;
	transform._14 = 0.0f;

	transform._21 = up.x * scale.y;
	transform._22 = up.y * scale.y;
	transform._23 = up.z * scale.y;
	transform._24 = 0.0f;

	transform._31 = front.x * scale.z;
	transform._32 = front.y * scale.z;
	transform._33 = front.z * scale.z;
	transform._34 = 0.0f;

	transform._41 = position.x;
	transform._42 = position.y;
	transform._43 = position.z;
	transform._44 = 1.0f;

	//発射方向
	this->direction = front;
}

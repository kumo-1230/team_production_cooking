#include "Character.h"
#include "EnemyManager.h"
#include "RayCast.h"
#include "stage.h"
#include "KeyInput.h"

//行列更新処理
void Character::UpdateTransfom()
{
	//スケール行列制作
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	//回転行列を制作
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	//位置行列を作成
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//三つの行列を組み合わせてワールド行列を作成
	DirectX::XMMATRIX W = S * R * T;

	//計算したワールド行列を取り出す
	DirectX::XMStoreFloat4x4(&transform, W);
}

void Character::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	////球のデバッグ
	//renderer->RenderSphere(rc, position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
	//円柱のデバッグ
	renderer->RenderCylinder(rc, position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}


bool Character::ApplyDamage(float dmage, EnemyManager* enemyManager)
{
	//ダメージが0の場合は健康状態を変更する必要がない
	if (dmage == 0) return false;

	//死亡している場合は健康状態を変更しない
	if (HP <= 0) return false;

	//ダメージ処理
	HP -= dmage;

	if (HP == 0)
	{
		OnDead(enemyManager);
	}
	else
	{
		OnDamaged();
	}

	//健康状態を変更した場合はtrueを返す
	return true;
}

bool Character::ApplyDamage(float dmage, float invincidleTime, EnemyManager* enemyManager)
{
	//ダメージが0の場合は健康状態を変更する必要がない
	if (dmage == 0) return false;

	//死亡している場合は健康状態を変更しない
	if (HP <= 0) return false;

	if (invincidleTimer > 0) return false;

	invincidleTimer = invincidleTime;

	//ダメージ処理
	HP -= dmage;

	if (HP == 0)
	{
		OnDead(enemyManager);
	}
	else
	{
		OnDamaged();
	}

	//健康状態を変更した場合はtrueを返す
	return true;
}

//衝撃を与える
void Character::AddImpulse(const DirectX::XMFLOAT3& impulse)
{
	velocity.x += impulse.x;
	velocity.y += impulse.y;
	velocity.z += impulse.z;
}

void Character::Move(float elapsedTime, float vx, float vz, float speed)
{
	//speed *= elapsedTime;
	//position.x += vx * speed;
	//position.z += vz * speed;

	KeyInput k;

	if (k.GetKeyDown(VK_SHIFT)&&coolTimer <= 0)
	{
		boostTimer = 0.05f;
		coolTimer = coolTime;
	}


	//移動方向ベクトル
	moveVecX = vx;
	moveVecZ = vz;


	if (boostTimer > 0.0f)
	{
		dash = true;
		acceleration = 200.0f;
		MaxMoveSpeed = speed * 3;
		boostTimer -= elapsedTime;
	}
	else
	{
		dash = false;
		acceleration = 50.0f;
		MaxMoveSpeed = speed;
	}
	//最大速度処理

	coolTimer -= elapsedTime;
}

void Character::Turn(float elapsedTime, float vx, float vz, float speed)
{
	speed *= elapsedTime;

	//進行ベクトルがゼロベクトルの場合は処理する必要なし
	float length = sqrtf(vx * vx + vz * vz);
	if (length == 0) return;

	//単位ベクトル化
	vx /= length;
	vz /= length;

	//自身の回転値から前方向を求める
	float frontX = sinf(angle.y);
	float frontZ = cosf(angle.y);

	//回転角を求めるため、二つの単位ベクトルの内積を計算する
	float dot = (frontX * vx) + (frontZ * vz);

	//ない席値は-1.0～1.0で表現されており、二つの単位ベクトルの角度が
	//小さいほど1.0に近づくという性質を利用して回転速度を調節する
	float rot = 1.0 - dot;
	if(rot > speed) rot = speed;

	//左右判定を行うために二つの単位ベクトルの外積を計算する
	float cross = (frontZ * vx) - (frontX * vz);

	//2Dの外積が制の場合か負の場合によって左右判定を行える
	//左右判定を行うことによって左右回転を選択する
	if (cross < 0.0f)
	{
		angle.y -= rot;
	}
	else
	{
		angle.y += rot;
	}

}

void Character::Jump(float speed)
{
	velocity.y = speed;
}

void Character::UpdateVelocity(float elapsedTime, const Stage* stage)
{

	//垂直速力更新
	UpdateVerticalVelocity(elapsedTime);

	//水平速力更新処理
	UpdateHorizontalVelocity(elapsedTime);

	//垂直移動更新処理
	UpdateVerticalMove(elapsedTime,stage);

	//水平移動更新処理
	UpdateHorizontalMove(elapsedTime,stage);

	{
	////重力処理
	//velocity.y += gravity * elapsedTime;

	////移動処理
	//position.y += velocity.y * elapsedTime;

	////地面判定
	//if (position.y < 0.0f)
	//{
	//	position.y = 0.0f;
	//	velocity.y = 0.0f;
	//	if (isGround == false)
	//	{
	//		isGround = true;
	//		OnLanding();
	//	}
	//}
	//else
	//{
	//	isGround = false;
	//}
	}
}


//速力更新
void Character::UpdateVerticalVelocity(float elapsedTime)
{
	//重力処理
	velocity.y += gravity * elapsedTime;

}

//垂直移動更新処理
void Character::UpdateVerticalMove(float elapsedTime,const Stage* stage)
{
	//移動処理
	float MoveY = velocity.y * elapsedTime;

	position.y += MoveY;

	//地面判定
	if (position.y < 0.0f)
	{
		position.y = 0.0f;
		velocity.y = 0.0f;
		if (isGround == false)
		{
			isGround = true;
			OnLanding();
		}
	}
	else
	{
		isGround = false;
	}

}

void Character::UpdateHorizontalVelocity(float elapsedTime)
{
	//XZ平面の速力を減速する
	float length = sqrtf( velocity.x * velocity.x + velocity.z * velocity.z);
	float friction = this->friction * elapsedTime;
	if (moveVecX == 0.0f && moveVecZ == 0.0f)
	{
		friction *= 5.0f; // 入力がないときは摩擦を強化
	}

	if (length > 0.0f)
	{
		//摩擦力

		//空中にいる間は摩擦力を減らす
		if (isGround == false) friction *= airControl;

		//摩擦による横方向の減速処理
		if (length > friction)
		{
			//if (isGround)
			//{
			//	velocity.x -= friction;
			//	velocity.z -= friction;
			//}
			float vx = velocity.x / length;
			float vz = velocity.z / length;
			velocity.x = vx * (length - friction);
			velocity.z = vz * (length - friction);
		}
		//横方向の速力が摩擦力いかになったら速力を無効か
		else
		{
			velocity.x = 0.0f;
			velocity.z = 0.0f;
		}
	}

	//XZ平面の速力を加速する
	if (length <= MaxMoveSpeed)
	{
		//移動ベクトルがゼロでないなら
		float moveVecLength = sqrtf(moveVecX * moveVecX + moveVecZ * moveVecZ);
		if (moveVecLength > 0.0f)
		{
			//加速力
			float acceleration = this->acceleration * elapsedTime;

			if (isGround == false) acceleration *= airControl;

			//移動ベクトルによる加速処理
			velocity.x += (moveVecX / moveVecLength) * acceleration;
			velocity.z += (moveVecZ / moveVecLength) * acceleration;

			//最大加速度制限
			{
				float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
				if (length > MaxMoveSpeed)
				{
					velocity.x = (velocity.x / length) * MaxMoveSpeed;
					velocity.z = (velocity.z / length) * MaxMoveSpeed;
				}
			}
		}
	}
	//移動ベクトルをリセット
	moveVecX = 0;
	moveVecZ = 0;
}

void Character::UpdateHorizontalMove(float elapsedTime, const Stage* stage)
{
	position.x += velocity.x * elapsedTime;
	position.z += velocity.z * elapsedTime;
}

//無敵時間
void Character::UpdateInvincidleTimer(float elapsedTime)
{
	if (invincidleTimer > 0.0f)
	{
		invincidleTimer -= elapsedTime;
	}
}

void Character::HitImpact(DirectX::XMFLOAT3 thisPos, DirectX::XMFLOAT3 targetPos, float power, Character* Target)
{
	//吹き飛ばす
	DirectX::XMFLOAT3 impulse;
	DirectX::XMVECTOR ThisPos = DirectX::XMLoadFloat3(&thisPos);
	DirectX::XMVECTOR TargetPos = DirectX::XMLoadFloat3(&targetPos);
	DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(TargetPos, ThisPos);
	//単位化
	Vec = DirectX::XMVector3Normalize(Vec);
	//スラカー倍する
	DirectX::XMStoreFloat3(&impulse, Vec);
	impulse.x *= power;
	impulse.y += 0;
	impulse.z *= power;

	Target->AddImpulse(impulse);

	//ヒットエフェクト
	DirectX::XMFLOAT3 e = Target->GetPosition();
	e.y += Target->GetHeight() * 0.5;
	//hitEffect->Play(e);

	////ヒットSE再生
	//hitSE->Play(false);
}

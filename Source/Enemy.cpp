#include "Enemy.h"
#include "EnemyManager.h"

//void Enemy::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* sr)
//{
//	Character::RenderDebugPrimitive(rc, sr);
//}

//�j��
void Enemy::Destroy(EnemyManager* enemyManager)
{
	enemyManager->Remove(this);
}

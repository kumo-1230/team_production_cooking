#include "EnemyManager.h"
#include "Collision.h"
#include "stage.h"
#include "Weapon.h"


void EnemyManager::Update(float elapsedTime,Player* player, const Stage* stage)
{
	for (Enemy* enemy : enemies)
	{
		enemy->Update(elapsedTime,player,stage,this);
		if (enemy->GetLifeTimer() < 0.0f)
		{
			enemy->Destroy(this);
		}
	}

	//廃棄処理
	//弾丸の範囲for文中でerase()すると不具合が発生するため
	//更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する
	for (Enemy* ene : removes)
	{
		//vectorから要素を削除する場合はイテレータで削除しなければならない
		std::vector<Enemy*>::iterator it = std::find(enemies.begin(), enemies.end(), ene);
		if (it != enemies.end())
		{
			enemies.erase(it);
		}
		//弾丸の廃棄処理
		delete ene;
	}

	//敵同士の衝突処理
	CollisionEnemyVsEnemies();

	//廃棄リストをクリア
	removes.clear();

}

void EnemyManager::Register(Enemy* enemy)
{
	enemies.push_back(enemy);
}

void EnemyManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	for (Enemy* enemy : enemies)
	{
		enemy->Render(rc, renderer);
	}
}

void EnemyManager::Clear()
{
	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}
	enemies.clear();
}

void EnemyManager::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	for (Enemy* enemy : enemies)
	{
		//renderer->RenderSphere(rc, enemy->GetPosition(), enemy->GetRadius(), DirectX::XMFLOAT4(0, 0, 0, 1));
		renderer->RenderCylinder(rc, enemy->GetPosition(), enemy->GetRadius(), enemy->GetHeight(), DirectX::XMFLOAT4(0, 0, 0, 1));
		enemy->RenderDebugPrimitive(rc, renderer);
	}
}

void EnemyManager::Remove(Enemy* enemy)
{
	//廃棄リストに追加
	removes.insert(enemy);
}

void EnemyManager::CollisionEnemyVsEnemies()
{
	//EnemyManager& enemyManager = EnemyManager::Instance();
	//すべての敵と総当たりで衝突処理
	int enemyConst = GetEnemyCount();

	for (int i = 0; i < enemyConst; i++)
	{
		for (int j = i + 1; j < enemyConst; j++)
		{
			Enemy* enemyA = GetEnemy(i);
			Enemy* enemyB = GetEnemy(j);

			//衝突処理
			DirectX::XMFLOAT3 outPositon;
			if (Collision::IntersectCylinderVsCylinder(
				enemyA->GetPosition(), enemyA->GetRadius(), enemyA->GetHeight(),
				enemyB->GetPosition(), enemyB->GetRadius(),enemyB->GetHeight(),
				outPositon))
			{
				enemyB->SetPosition(outPositon);
			}
		}
	}

}

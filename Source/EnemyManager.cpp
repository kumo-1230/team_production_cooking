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

	//�p������
	//�e�ۂ͈̔�for������erase()����ƕs����������邽��
	//�X�V�������I�������ɔj�����X�g�ɐς܂ꂽ�I�u�W�F�N�g���폜����
	for (Enemy* ene : removes)
	{
		//vector����v�f���폜����ꍇ�̓C�e���[�^�ō폜���Ȃ���΂Ȃ�Ȃ�
		std::vector<Enemy*>::iterator it = std::find(enemies.begin(), enemies.end(), ene);
		if (it != enemies.end())
		{
			enemies.erase(it);
		}
		//�e�ۂ̔p������
		delete ene;
	}

	//�G���m�̏Փˏ���
	CollisionEnemyVsEnemies();

	//�p�����X�g���N���A
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
	//�p�����X�g�ɒǉ�
	removes.insert(enemy);
}

void EnemyManager::CollisionEnemyVsEnemies()
{
	//EnemyManager& enemyManager = EnemyManager::Instance();
	//���ׂĂ̓G�Ƒ�������ŏՓˏ���
	int enemyConst = GetEnemyCount();

	for (int i = 0; i < enemyConst; i++)
	{
		for (int j = i + 1; j < enemyConst; j++)
		{
			Enemy* enemyA = GetEnemy(i);
			Enemy* enemyB = GetEnemy(j);

			//�Փˏ���
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

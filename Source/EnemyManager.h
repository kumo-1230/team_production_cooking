#pragma once

#include <vector>
#include <set>
#include "Enemy.h"

class Stage;

//�V���O���g��
class EnemyManager
{

private:
	std::vector<Enemy*> enemies;
	std::set<Enemy*> removes;

public:
	EnemyManager() {}
	~EnemyManager() {}

public:
	////////////////////////////////////////

	//�G�l�~�[�擾
	Enemy* GetEnemy(int index) { return enemies.at(index); }
	
	//�����擾
	float GetEnemyHeight(int index) const { return enemies.at(index)->GetHeight(); }

	//�G�l�~�[���擾
	int GetEnemyCount() const { return static_cast<int> (enemies.size()); }

	//�G�l�~�[�|�W�V�����擾
	const DirectX::XMFLOAT3& GetEnemyPos(int index) const { return enemies.at(index)->GetPosition(); }

	////////////////////////////////////////

public:
	void Update(float elapsedTime,Player* player, const Stage* stage);

	void Render(const RenderContext& rc, ModelRenderer* renderer);

	//�f�o�b�O�v���~�e�B�u�`��
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	//�G�l�~�[�o�^
	void Register(Enemy* enemy);

	//�G�l�~�[�폜
	void Clear();

	//�G�l�~�[�폜
	void Remove(Enemy* enemy);

private:
	//�G�l�~�[���m�̏Փˏ���
	void CollisionEnemyVsEnemies();
};
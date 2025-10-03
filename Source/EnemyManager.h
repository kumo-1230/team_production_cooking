#pragma once

#include <vector>
#include <set>
#include "Enemy.h"

class Stage;

//シングルトン
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

	//エネミー取得
	Enemy* GetEnemy(int index) { return enemies.at(index); }
	
	//高さ取得
	float GetEnemyHeight(int index) const { return enemies.at(index)->GetHeight(); }

	//エネミー数取得
	int GetEnemyCount() const { return static_cast<int> (enemies.size()); }

	//エネミーポジション取得
	const DirectX::XMFLOAT3& GetEnemyPos(int index) const { return enemies.at(index)->GetPosition(); }

	////////////////////////////////////////

public:
	void Update(float elapsedTime,Player* player, const Stage* stage);

	void Render(const RenderContext& rc, ModelRenderer* renderer);

	//デバッグプリミティブ描画
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	//エネミー登録
	void Register(Enemy* enemy);

	//エネミー削除
	void Clear();

	//エネミー削除
	void Remove(Enemy* enemy);

private:
	//エネミー同士の衝突処理
	void CollisionEnemyVsEnemies();
};
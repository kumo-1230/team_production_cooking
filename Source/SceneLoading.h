#pragma once

#include "System/Sprite.h"
#include "Scene.h"

#include <thread>

//ローディング
class SceneLoading : public Scene
{
private:
	Sprite* sprite = nullptr;
	float angle = 0.0f;
	Scene* nextScene = nullptr;

	std::thread* thread = nullptr;

private:
	//ローディングスレッド
	static void LoadingThread(SceneLoading* scene);

public:
	//SceneLoading(){}
	SceneLoading(Scene* nexetScene): nextScene(nexetScene){}
	~SceneLoading() override {}

	//初期化
	void Initialize() override;

	//終了化
	void Finalize() override;

	//更新処理
	void Update(float elapsedTime) override;

	//描画処理
	void Render() override;

	//GUI描画
	void DrawGUI() override;
};
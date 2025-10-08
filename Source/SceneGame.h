#pragma once

#include "stage.h"
//#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
#include "Camera.h"
#include <memory>
#include "EnemyManager.h"
#include "Player.h"
#include "Menu.h"
#include <vector>
#include "StageManager.h"


// ゲームシーン
class SceneGame : public Scene
{
private:
	std::unique_ptr<Player> player                     = nullptr;
	std::unique_ptr<EnemyManager> enemyManager         = nullptr;
	std::unique_ptr<Camera> camera                     = nullptr;
	std::unique_ptr<StageManager> stageManager         = nullptr;
	std::unique_ptr<CameraController> cameraController = nullptr;

	bool build = true;

	//マウス
	bool g_mouseCaptured = true;  // true = ゲームがマウスを奪っている

public:
	SceneGame();
	//~SceneGame() {};
	~SceneGame() override {}

	// 初期化
	//void Initialize();
	void Initialize() override;

	// 終了化
	//void Finalize();
	void Finalize() override;

	// 更新処理
	//void Update(float elapsedTime);
	void Update(float elapsedTime) override;

	// 描画処理
	//void Render();
	void Render() override;

	// GUI描画
	//void DrawGUI();
	void DrawGUI() override;

	float gameLimit = 300;

};

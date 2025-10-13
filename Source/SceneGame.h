#pragma once

#include "stage.h"
//#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
#include "Camera.h"
#include <memory>
#include "Player.h"
#include "Menu.h"
#include <vector>
#include "StageManager.h"
#include "foodManager.h"
#include "omurice.h"
#include "Dish.h"

// ゲームシーン
class SceneGame : public Scene
{
private:
	std::unique_ptr<Player> player                     = nullptr;
	std::unique_ptr<Camera> camera                     = nullptr;
	std::unique_ptr<StageManager> stageManager         = nullptr;
	std::unique_ptr<CameraController> cameraController = nullptr;
	std::unique_ptr<FoodManager> foodManager           = nullptr;
	std::unique_ptr<DishManager> dishManager           = nullptr;

	bool build = false;

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

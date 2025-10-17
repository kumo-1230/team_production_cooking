#pragma once

#include "stage.h"
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
#include "ScoreRender.h"
#include "KeyInput.h"

#define SCORE_WIDTH 44
#define SCORE_HEIGHT 60
#define SCORE_MASK   44

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
	std::unique_ptr<KeyInput> key                      = nullptr;
	std::unique_ptr<Menu> menu                         = nullptr;

	std::unique_ptr<Sprite> scoreNum = nullptr;
	std::unique_ptr<Sprite> score = nullptr;
	std::unique_ptr<Sprite> minus = nullptr;
	std::unique_ptr<Sprite> en = nullptr;
	std::unique_ptr<Sprite> ko = nullptr;
	std::unique_ptr<Sprite> omu[3] = { nullptr,nullptr,nullptr };

	std::unique_ptr<Sprite> black = nullptr;
	std::unique_ptr<Sprite> receipt = nullptr;
 	std::unique_ptr<Sprite> finish = nullptr;


	KeyInput keyInput;
	scoreRender sr;
	bool build = true;

	float resalttimer = 0;

	float blackAlpha = 0;
	float blackY = 1080;
	int money = 0;

	//マウス
	bool g_mouseCaptured = true;  // true = ゲームがマウスを奪っている

	struct Vertex
	{
		DirectX::XMFLOAT2 pos;
	};

	float width = 88;
    float height = 120;

	bool isResult = false;
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

	void AfterUpdateRender();

	// 描画処理
	//void Render();
	void Render() override;
	// GUI描画
	//void DrawGUI();
	void DrawGUI() override;

	float gameLimit = 3;

	float finishTimer = 0;

	float easeOutBounse(float x)
	{
		const float n1 = 7.5625;
		const float d1 = 2.75;

		if (x < 1 / d1) {
			return n1 * x * x;
		}
		else if (x < 2 / d1) {
			return n1 * (x -= 1.5 / d1) * x + 0.75;
		}
		else if (x < 2.5 / d1) {
			return n1 * (x -= 2.25 / d1) * x + 0.9375;
		}
		else {
			return n1 * (x -= 2.625 / d1) * x + 0.984375;
		}
	}
};

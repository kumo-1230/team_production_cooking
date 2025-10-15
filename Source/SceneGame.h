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
#include "ScoreRender.h"

#define SCORE_WIDTH 88
#define SCORE_HEIGHT 120
#define SCORE_MASK   88

// �Q�[���V�[��
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

	bool build = false;

	int money = 0;

	scoreRender sr;

	//�}�E�X
	bool g_mouseCaptured = true;  // true = �Q�[�����}�E�X��D���Ă���

	struct Vertex
	{
		DirectX::XMFLOAT2 pos;
	};

	float width = 88;
    float height = 120;
public:
	SceneGame();
	//~SceneGame() {};
	~SceneGame() override {}

	// ������
	//void Initialize();
	void Initialize() override;

	// �I����
	//void Finalize();
	void Finalize() override;

	// �X�V����
	//void Update(float elapsedTime);
	void Update(float elapsedTime) override;

	// �`�揈��
	//void Render();
	void Render() override;
	// GUI�`��
	//void DrawGUI();
	void DrawGUI() override;

	float gameLimit = 300;

};

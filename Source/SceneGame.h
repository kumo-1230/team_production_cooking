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

	std::unique_ptr<Sprite> scoreNum = nullptr;
	std::unique_ptr<Sprite> score = nullptr;
	std::unique_ptr<Sprite> minus = nullptr;
	std::unique_ptr<Sprite> omu[3] = { nullptr,nullptr,nullptr };


	scoreRender sr;
	bool build = true;

	int money = 0;


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

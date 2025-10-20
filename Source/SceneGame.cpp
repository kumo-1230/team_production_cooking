
#include "System/Graphics.h"
#include "SceneGame.h"
#include "Player.h"
#include "common.h"
#include "System/Input.h"
#include "SceneManager.h"
#include "SceneResult.h"
#include "foodManager.h"
#include "Floor.h"
#include "SceneTitle.h"
#include "System/Audio.h"
#include "SceneLoading.h"
#include <imgui.h>

//#define DEBUG

SceneGame::SceneGame()
{
}

// ������
void SceneGame::Initialize()
{
	// �J�[�\�����\���ɂ���
	ShowCursor(FALSE);

	srand((unsigned int)time(NULL));
	//�X�e�[�W������
	stageManager = std::make_unique<StageManager>();

	player = std::make_unique<Player>();

	scoreNum = std::make_unique<Sprite>("Data/Sprite/Number.png");
	score = std::make_unique<Sprite>("Data/Sprite/Score.png");
	minus = std::make_unique<Sprite>("Data/Sprite/minus.png");
	en = std::make_unique<Sprite>("Data/Sprite/en.png");
	ko = std::make_unique<Sprite>("Data/Sprite/ko.png");
	tuto = std::make_unique<Sprite>("Data/tutorial/tuto.png");
	tuto2 = std::make_unique<Sprite>("Data/tutorial/tuto2.png");

	omu[0] = std::make_unique<Sprite>("Data/Sprite/UI/order1_tomato.png");
	omu[1] = std::make_unique < Sprite>("Data/Sprite/UI/order_demi-glace.png");
	omu[2] = std::make_unique<Sprite>("Data/Sprite/UI/order3_white.png");

	finish = std::make_unique<Sprite>("Data/Sprite/timeUp.png");
	receipt = std::make_unique<Sprite>("Data/Sprite/receipt.png");
	black = std::make_unique<Sprite>("Data/Sprite/black.png");

	checkFalse = std::make_unique<Sprite>("Data/Sprite/check_false.png");

	setMusic = Audio::Instance().LoadAudioSource("Data/Sound/Set.wav");
	showMoney = Audio::Instance().LoadAudioSource("Data/Sound/ShowMoney.wav");

	//�J����������
	Graphics& graphics = Graphics::Instance();
	camera.reset(new Camera);
	camera->SetLookAt(
		DirectX::XMFLOAT3(0, 10, -5),
		DirectX::XMFLOAT3(0, 0, 0),
		DirectX::XMFLOAT3(0, 1, 0)
	);
	camera->SetPerspectibeFov(
		DirectX::XMConvertToRadians(45),
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);

	//�J�����R���g���[���[������
	cameraController = std::make_unique<CameraController>();

	//�e�X�g�p
	foodManager.reset(new FoodManager);
	dishManager.reset(new DishManager);

	auto chickinrice = std::make_unique<Rice>();
	chickinrice->setPosition({ 5,5,0 });
	chickinrice->setScale({ 0.01f,0.01f,0.01f });
	chickinrice.get()->SetLv(2);

	chickinrice.get()->SetOmuType(1);
	foodManager->Register(std::move(chickinrice));

	dishManager.reset(new DishManager);

	DishSet();

	stageManager->SetBuild(build);

	key = std::make_unique<KeyInput>();

	//menu.reset(new Menu());
	//menu->SetButton("Data/Sprite/sturt.png", { SCREEN_W * 0.8 - 150,SCREEN_H * 0.8 }, { 300,150 }, 0, 0, true);
	//menu->SetMenuStart(true);

	setMusic->Play(true);
	setMusic->SetVolume(0.5f);

	SpriteTimer = std::make_unique<Sprite>("Data/Sprite/UI/timer.png");
	SpriteTimerTheSilentTrackerOfPassingMoments = std::make_unique<Sprite>("Data/Sprite/UI/long_hand.png");

	SpritMenu = std::make_unique<Sprite>("Data/Sprite/menu.png");
}

// �I����
void SceneGame::Finalize()
{
	player->Finalize();
}

void SceneGame::DishSet()
{
	auto dish = std::make_unique<Dish>();
	dish->setPosition({  8 * 2.0f,2.0f,4 * 2.0f });
	dishManager->Register(std::move(dish));

	dish = std::make_unique<Dish>();
	dish->setPosition({ 9 * 2.0f,2.0f,5 * 2.0f });
	dishManager->Register(std::move(dish));

	dish = std::make_unique<Dish>();
	dish->setPosition({ 10 * 2.0f,2.0f,4 * 2.0f });
	dishManager->Register(std::move(dish));
}

// �X�V����
void SceneGame::Update(float elapsedTime)
{
	if (isResult == true)
	{
		AfterUpdateRender();
	}
	GamePad& gamePad = Input::Instance().GetGamePad();

	ShowCursor(TRUE); // �J�[�\�����B��

	if (build)
	{
		if (money < stageManager->GetMoney())
		{
			money += 23;
			if (money > stageManager->GetMoney()) // �s���߂��h�~
				money = stageManager->GetMoney();
		}
		else if (money > stageManager->GetMoney())
		{
			money -= 23;
			if (money < stageManager->GetMoney()) // �s���߂��h�~
				money = stageManager->GetMoney();
		}
		player->SetMoney(stageManager->GetMoney());
	}
	else
	{
		setMusic->Stop();
		gameLimit += 1 * elapsedTime;
		if (gameLimit > gameLimitBank)
		{
			finishTimer += 1 * elapsedTime;
			if (finishTimer > 1)
			{
				finishTimer = 1;
			}
			return;
		}

		if (money < player.get()->getScore())
		{
			money += 23;
			if (money > player.get()->getScore()) // �s���߂��h�~
				money = player.get()->getScore();
		}
		else if (money > player.get()->getScore())
		{
			money -= 23;
			if (money < player.get()->getScore()) // �s���߂��h�~
				money = player.get()->getScore();
		}
	}

	//gameLimit -= 1 * elapsedTime;
	//if (gameLimit < 0)
	//{
	//	SceneManager::Instance().ChangeScene(new SceneTitle());
	//	return;
	//}

	//�J�����R���g���[���[�X�V����
	//DirectX::XMFLOAT3 target = player->GetPosition();
	//�J���������ݒ�(�ύX�̗]�n����)
	DirectX::XMFLOAT3 target = { 15,0,10 };
	cameraController->SetTarget(target);

	POINT center;
	center.x = SCREEN_W * 0.5f;
	center.y = SCREEN_H * 0.5f;

	//���݂̃J�[�\���ʒu���擾
	//POINT cursor;
	//GetCursorPos(&cursor);

	////�N���C�A���g���W�ɕϊ�
	//ScreenToClient(Graphics::Instance().GetWindowHandle(), &cursor);

	//float ax = (float)(cursor.x - center.x);
	//float ay = (float)(cursor.y - center.y);

	cameraController->Updeate(elapsedTime, camera.get());

	//// �J�[�\���𒆉��ɖ߂�
	//POINT screenCenter{ (LONG)(SCREEN_W / 2), (LONG)(SCREEN_H / 2) };
	//ClientToScreen(Graphics::Instance().GetWindowHandle(), &screenCenter);
	//SetCursorPos(screenCenter.x, screenCenter.y);

	int num{ -1 };

	//menu->Updeat(&num);

	checkTimer -= 1 * elapsedTime;

	if (build)
	{
		if (key->GetKeyDown(VK_RETURN) || num == 0)
		{
			bool check = stageManager->BuildCheck();
			if (check)
			{
				build = false;
				stageManager->SetBuild(build);
				stageManager->BuildingMap();
			}
			else
			{
				checkTimer = 1.0f;
			}
		}
	}
	else
	{
		if (key->GetKeyDown(VK_RETURN) || num == 0)
		{
			build = true;
			stageManager->SetBuild(build);
			stageManager->SetPlayerPos();
			foodManager->RemoveAllFood();
			player->SetDish(nullptr);
			player->SetFood(nullptr);
			player->SetMoney(0);
			dishManager->RemoveAllDishes();
			DishSet();
			gameLimit = 0;
		}
	}

	//�X�e�[�W�X�V����
	stageManager->Update(elapsedTime,dishManager.get(),player.get(),foodManager.get());
	//if (build)
	//{
	//	money = stageManager->GetMoney();
	//}
	if(build == false)
	{
		foodManager->Update(elapsedTime);

		dishManager->Update(elapsedTime);
		//�v���C���[�X�V����
		player->Update(elapsedTime, camera.get(), stageManager.get(), foodManager.get(),dishManager.get());
	}
}

void SceneGame::AfterUpdateRender()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ShapeRenderer* shapeRenderer = graphics.GetShapeRenderer();
	ModelRenderer* modelRenderer = graphics.GetModelRenderer();

	// �`�揀��
	RenderContext rc;
}

// �`�揈��
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ShapeRenderer* shapeRenderer = graphics.GetShapeRenderer();
	ModelRenderer* modelRenderer = graphics.GetModelRenderer();

	// �`�揀��
	RenderContext rc;
	rc.deviceContext = dc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f };	// ���C�g�����i�������j
	rc.renderState = graphics.GetRenderState();

	//�J�����p�����[�^�ݒ�
	rc.view = camera->GetView();
	rc.projection = camera->GetProjection();

	{
		//// �r���[�s��
		//{
		//	DirectX::XMFLOAT3 eye = { 0, 10, -10 };	// �J�����̎��_�i�ʒu�j
		//	DirectX::XMFLOAT3 focus = { 0, 0, 0 };	// �J�����̒����_�i�^�[�Q�b�g�j
		//	DirectX::XMFLOAT3 up = { 0, 1, 0 };		// �J�����̏����

		//	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
		//	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
		//	DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);
		//	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
		//	DirectX::XMStoreFloat4x4(&rc.view, View);
		//}

		//// �v���W�F�N�V�����s��
		//{
		//	float fovY = DirectX::XMConvertToRadians(45);	// ����p
		//	float aspectRatio = graphics.GetScreenWidth() / graphics.GetScreenHeight();	// ��ʏc���䗦
		//	float nearZ = 0.1f;	// �J�������f���o���̍ŋߋ���
		//	float farZ = 1000.0f;	// �J�������f���o���̍ŉ�����
		//	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY, aspectRatio, nearZ, farZ);
		//	DirectX::XMStoreFloat4x4(&rc.projection, Projection);
		//}
	}

	// 3D���f���`��
	{
		//�X�e�[�W�`��
		stageManager->Render(rc, modelRenderer);

		if (build == false)
		{
			//�v���C���[�`��
			player->Render(rc, modelRenderer);

			//���ѕ`��
			foodManager->Render(rc, modelRenderer);

			//�M�`��
			dishManager->Render(rc, modelRenderer);
		}
	}

	// 3D�f�o�b�O�`��
	{
		//stageManager->RenderDebugPrimitive(rc, shapeRenderer);
		//if (build == false)
		//{
		//	//�v���C���[�f�o�b�O�v���~�e�B�u�`��
		//	player->RenderDebugPrimitive(rc, shapeRenderer);

		//}
	}

	// 2D�X�v���C�g�`��
	{
		score->Render(rc, 0, 10, 0, SCREEN_W / 1.5, SCREEN_H / 1.5, 0, 1, 1, 1, 1);
		sr.ScoreRenderDigit(rc, scoreNum.get(), minus.get(), en.get(), money, SCORE_WIDTH, SCORE_HEIGHT, 150, 20);
		SpritMenu->Render(rc, SCREEN_W * 0.3f, SCREEN_H * 0.8f - 150, 0, 1268, 350, 0, 1, 1, 1, 1);
		if (build)
		{
			tuto->Render(rc, 1800 + -1 * a, 0, 0, a * 1.5, 1.5 * a * 0.5625, 0, 1, 1, 1, 1);
			a -= 10;
			if (a < 300)
			{
				a = 300;
			}
			//menu->Render(rc, MENU::BACK_OFF);
			if (checkTimer >= 0)
			{
				checkFalse->Render(rc, SCREEN_W * 0.5f - 300, SCREEN_H * 0.5f - 150, 0, 600, 300, 0, 1, 1, 1, 1);
			}
		}
		else
		{
			tuto2->Render(rc, 1800 + -1 * a, 0, 0, a * 1.5, 1.5 * a * 0.5625, 0, 1, 1, 1, 1);
			float timerAngle = 360.0f * (gameLimit / gameLimitBank);
			SpriteTimer->Render(rc, SCREEN_W * 0.5f - 50, 0, 0, 100, 100, 0, 1, 1, 1, 1);
			SpriteTimerTheSilentTrackerOfPassingMoments->Render(rc, SCREEN_W * 0.5f - 50, 0, 0, 100, 100, timerAngle, 1, 1, 1, 1);


#ifdef DEBUG
			//�Ȃ񂩂̃|�W�V����������Ă���
			ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
			//�\���ꏊ
			ImGui::SetNextWindowPos(ImVec2(pos.x + 10, pos.y + 10), ImGuiCond_Once);
			//�傫��
			ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

			if (ImGui::Begin("timer", nullptr, ImGuiWindowFlags_None))
			{
				//�g�����X�t�H�[��
				//if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
				{
					//�ʒu
					ImGui::InputFloat("gameLimit", &gameLimit);
					ImGui::InputFloat("gameLimitBank", &gameLimitBank);
					ImGui::InputFloat("timerAngle", &timerAngle);


				}
			}
			ImGui::End();

#endif // DEBUG





			a -= 10;
			if (a < 300)
			{
				a = 300;
			}
			for (int i = 0; i < 4; i++)
			{
				switch (player.get()->orderSlot[i])
				{
				case 1:
					omu[0]->Render(rc, 0, 120 + i * 220, 0, 180, 180, 0, 1, 1, 1, 1);
					break;
				case 2:
					omu[1]->Render(rc, 0, 120 + i * 220, 0, 180, 180, 0, 1, 1, 1, 1);
					break;
				case 3:
					omu[2]->Render(rc, 0, 120 + i * 220, 0, 180, 180, 0, 1, 1, 1, 1);
					break;
				default:
					break;
				}
			}
			foodManager->Render2D(rc);
			stageManager->Render2D(rc);
		}


		if (gameLimit > gameLimitBank)
		{
			float x = easeOutBounse(finishTimer);
			finish->Render(rc, 571, 420 * x, 0, 778, 240, 0, 1, 1, 1, 1);
			if (keyInput.GetKeyDown(VK_RETURN) && x >= 1)isResult = true;
			if (isResult)
			{
				blackAlpha += 0.01f;
				black->Render(rc, 0, 0, 0, 1920, 1080, 0, 1, 1, 1, blackAlpha);
				if (blackAlpha > 1) blackAlpha = 1;
				if (blackAlpha >= 1)
				{
					blackY -= 2.0f;
					if (blackY < -500)blackY = -500;
					receipt->Render(rc, 610, blackY, 0, 700, 1900, 0, 1, 1, 1, 1);
				}
				if (blackY <= -500)
				{
					resalttimer += 0.01f;
					player.get()->omu[0].omuSprite->Render(rc, 650, 100, 0, 180, 180, 0, 1, 1, 1, resalttimer);
					sr.ScoreRenderDigit(rc, scoreNum.get(), minus.get(), ko.get(), player.get()->omu[0].count, SCORE_WIDTH, SCORE_HEIGHT, 830, 130);
					sr.ScoreRenderDigit(rc, scoreNum.get(), minus.get(), en.get(), player.get()->omu[0].charge, SCORE_WIDTH, SCORE_HEIGHT, 1030, 130);
					player.get()->omu[1].omuSprite->Render(rc, 650, 380, 0, 180, 180, 0, 1, 1, 1, resalttimer);
					sr.ScoreRenderDigit(rc, scoreNum.get(), minus.get(), ko.get(), player.get()->omu[1].count, SCORE_WIDTH, SCORE_HEIGHT, 830, 410);
					sr.ScoreRenderDigit(rc, scoreNum.get(), minus.get(), en.get(), player.get()->omu[1].charge, SCORE_WIDTH, SCORE_HEIGHT, 1030, 410);
					player.get()->omu[2].omuSprite->Render(rc, 650, 660, 0, 180, 180, 0, 1, 1, 1, resalttimer);
					sr.ScoreRenderDigit(rc, scoreNum.get(), minus.get(), ko.get(), player.get()->omu[2].count, SCORE_WIDTH, SCORE_HEIGHT, 830, 690);
					sr.ScoreRenderDigit(rc, scoreNum.get(), minus.get(), en.get(), player.get()->omu[2].charge, SCORE_WIDTH, SCORE_HEIGHT, 1030, 690);
					if (keyInput.GetKey(VK_RETURN))
					{
						SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTitle()));
					}
				}
			}
		}
	}

}

// GUI�`��
void SceneGame::DrawGUI()
{
	//�v���C���[�f�o�b�O�`��
	//player->DrawDebugGUI();
	player->DrawDebugGUI();
}

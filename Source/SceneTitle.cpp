#include "System/Graphics.h"
#include "SceneTitle.h"
#include "System/Input.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "common.h"
#include "System/Audio.h"

SceneTitle::SceneTitle()
{
}

void SceneTitle::CostChange(int pwMode,bool Up)
{
	if (Up)
	{
	}
	else
	{
	}
}

bool SceneTitle::PwJudge(int pwMode, bool Up)
{
	if (Up)
	{
	}
	else
	{
	}
	return false;
}

//初期化
void SceneTitle::Initialize()
{
	//スプライト初期化
	sprite = std::make_unique<Sprite>("Data/Sprite/titleSpr.png");
	straight = std::make_unique<Sprite>("Data/Sprite/sutoreto.png");
	homing = std::make_unique<Sprite>("Data/Sprite/hominngu.png");
	rotate = std::make_unique<Sprite>("Data/Sprite/roring.png");

	startSE = Audio::Instance().LoadAudioSource("Data/Sound/Title.wav");
	//タイトル画面の分岐ボタン
	titleStartMenu.reset(new Menu());
	titleStartMenu->SetButton("Data/Sprite/start1.png", {600,700},{200,100},0,0,true);
	titleStartMenu->SetMenuStart(true);

	startSE->Play(true);
	startSE->SetVolume(0.5);
}

//終了化
void SceneTitle::Finalize()
{
	startSE->Stop();
}

//更新処理
void SceneTitle::Update(float elapsedTime)
{
	// カーソルを非表示にする
	ShowCursor(TRUE);

	GamePad& gamePad = Input::Instance().GetGamePad();

	////何かボタンを押したら
	//const GamePadButton anyButton = GamePad::BTN_A | GamePad::BTN_B | GamePad::BTN_X | GamePad::BTN_Y;

	titleStartMenu->Updeat(&menuNum);

	if (titleStartMenu->GetMenyuStart())
	{
		switch (menuNum)
		{
		case 0:
			SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame()));
			break;
		case 1:
			titleStartMenu->SetMenuStart(false);
			break;
		}
	}

	menuNum = -1;
}

void SceneTitle::PwUp(int pwMode, bool Up)
{
	if (Up)
	{
		if (PwJudge(pwMode, Up))
		{
			CostChange(pwMode, Up);
		}
	}
	else
	{
		if (PwJudge(pwMode, Up))
		{
			CostChange(pwMode, Up);
		}
	}
}

//描画処理
void SceneTitle::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	RenderState* renderState = graphics.GetRenderState();

	//描画準備
	RenderContext rc;
	rc.deviceContext = dc;
	rc.renderState = graphics.GetRenderState();

	//2Dスプライト描画
	{
		//タイトル描画
		float screenWidth = static_cast<float>(graphics.GetScreenWidth());
		float screenHeight = static_cast<float>(graphics.GetScreenHeight());
		sprite->Render(rc,
			0, 0, 0, screenWidth, screenHeight,
			0,
			1, 1, 1, 1);

		titleStartMenu->Render(rc, MENU::BACK_OFF);

	}
}


void SceneTitle::DrawGUI()
{
}

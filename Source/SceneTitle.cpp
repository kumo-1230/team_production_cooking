#include "System/Graphics.h"
#include "SceneTitle.h"
#include "System/Input.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "common.h"

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

//������
void SceneTitle::Initialize()
{
	//�X�v���C�g������
	sprite = std::make_unique<Sprite>("Data/Sprite/Title.png");
	straight = std::make_unique<Sprite>("Data/Sprite/sutoreto.png");
	homing = std::make_unique<Sprite>("Data/Sprite/hominngu.png");
	rotate = std::make_unique<Sprite>("Data/Sprite/roring.png");

	//�^�C�g����ʂ̕���{�^��
	titleStartMenu.reset(new Menu());
	titleStartMenu->SetButton("Data/Sprite/test2.png", { SCREEN_W * 0.5 - 50,SCREEN_H * 0.7},{100,100},0,0,true);
	titleStartMenu->SetButton("Data/Sprite/test.png", { SCREEN_W * 0.5 - 50,SCREEN_H * 0.8},{100,100},1,1,true);
	titleStartMenu->SetMenuStart(true);

	//�X�L���c���[���򏈗�
	titlePwUpMenu.reset(new Menu());
	titlePwUpMenu->SetButton("Data/Sprite/purasu.png", { SCREEN_W * 0.1 - 50,SCREEN_H * 0.3 }, { 100,100 }, 1, PwUp::STRING_UP,true);
	titlePwUpMenu->SetButton("Data/Sprite/mainas.png", { SCREEN_W * 0.2 - 50,SCREEN_H * 0.3 }, { 100,100 }, 1, PwUp::STRING_DOWN,true);
	titlePwUpMenu->SetButton("Data/Sprite/purasu.png", { SCREEN_W * 0.3 - 50,SCREEN_H * 0.3 }, { 100,100 }, 1, PwUp::HOMING_UP,true);
	titlePwUpMenu->SetButton("Data/Sprite/mainas.png", { SCREEN_W * 0.4 - 50,SCREEN_H * 0.3 }, { 100,100 }, 1, PwUp::HOMING_DOWN,true);
	titlePwUpMenu->SetButton("Data/Sprite/purasu.png", { SCREEN_W * 0.5 - 50,SCREEN_H * 0.3 }, { 100,100 }, 1, PwUp::ROTATE_UP,true);
	titlePwUpMenu->SetButton("Data/Sprite/mainas.png", { SCREEN_W * 0.6 - 50,SCREEN_H * 0.3 }, { 100,100 }, 1, PwUp::ROTATE_DOWN,true);
	titlePwUpMenu->SetMenuStart(false);
	titlePwUpMenu->GetButton(0)->SetRenderMode(BUTTON_R_MODE::NORMAL);
	titlePwUpMenu->GetButton(1)->SetRenderMode(BUTTON_R_MODE::HALF_INVISIBLE);
	titlePwUpMenu->GetButton(2)->SetRenderMode(BUTTON_R_MODE::NORMAL);
	titlePwUpMenu->GetButton(3)->SetRenderMode(BUTTON_R_MODE::HALF_INVISIBLE);
	titlePwUpMenu->GetButton(4)->SetRenderMode(BUTTON_R_MODE::NORMAL);
	titlePwUpMenu->GetButton(5)->SetRenderMode(BUTTON_R_MODE::HALF_INVISIBLE);
}

//�I����
void SceneTitle::Finalize()
{

}

//�X�V����
void SceneTitle::Update(float elapsedTime)
{
	// �J�[�\�����\���ɂ���
	ShowCursor(TRUE);

	if (titlePwUpMenu->GetMenyuStart() == false) titleStartMenu->SetMenuStart(true);

	GamePad& gamePad = Input::Instance().GetGamePad();

	////�����{�^������������
	//const GamePadButton anyButton = GamePad::BTN_A | GamePad::BTN_B | GamePad::BTN_X | GamePad::BTN_Y;

	titleStartMenu->Updeat(&menuNum);
	titlePwUpMenu->Updeat(&menuNum);

	if (titleStartMenu->GetMenyuStart())
	{
		switch (menuNum)
		{
		case 0:
			SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame()));
			break;
		case 1:
			titleStartMenu->SetMenuStart(false);
			titlePwUpMenu->SetMenuStart(true);
			break;
		}
	}
	else if (titlePwUpMenu->GetMenyuStart())
	{
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

//�`�揈��
void SceneTitle::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	RenderState* renderState = graphics.GetRenderState();

	//�`�揀��
	RenderContext rc;
	rc.deviceContext = dc;
	rc.renderState = graphics.GetRenderState();

	//2D�X�v���C�g�`��
	{
		//�^�C�g���`��
		float screenWidth = static_cast<float>(graphics.GetScreenWidth());
		float screenHeight = static_cast<float>(graphics.GetScreenHeight());
		sprite->Render(rc,
			0, 0, 0, screenWidth, screenHeight,
			0,
			1, 1, 1, 1);

		titleStartMenu->Render(rc, MENU::BACK_OFF);
		titlePwUpMenu->Render(rc, MENU::BACK_ON);

		if (titlePwUpMenu->GetMenyuStart())
		{
			straight->Render(rc, SCREEN_W * 0.1 + 0.0f, SCREEN_H * 0.2, 0,
				200.0f, 100.0f, 0, 1, 1, 1, 1);
		}

	}
}


void SceneTitle::DrawGUI()
{
}

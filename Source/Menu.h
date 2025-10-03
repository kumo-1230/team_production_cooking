#pragma once
#include "ButtonManager.h"
#include "KeyInput.h"


namespace MENU
{
	//�w�i����
	const int BACK_OFF (0);
	//�w�i�Ȃ�
	const int BACK_ON (1);
}

class Menu
{
private:
	//���j���[���\������Ă邩
	bool menuStart = false;
	//int menuMode = 0;
	std::unique_ptr<ButtonManager> buttonManager;
	//�w�i�̉摜
	std::unique_ptr<Sprite> sprBack;

	KeyInput keyInput;

public:
	Menu();
	~Menu();

public:
	////////////////////////////

	//�{�^���ǉ�
	void SetButton(const char* fileName, DirectX::XMFLOAT2 p, DirectX::XMFLOAT2 l, int la, int n, bool v)
	{
		buttonManager->SetButton(fileName, p, l, la, n, v);
	}

	//���j���[��\�����邩
	void SetMenuStart(bool S) { menuStart = S; }
	//���j���[��\�����Ă邩
	bool GetMenyuStart() { return menuStart; }
	//����̃{�^�����Q�b�g
	Button* GetButton(int i) { return buttonManager->GetButton(i); }

	////////////////////////////
public:

	void Updeat(int* hb);
	void Render(const RenderContext& rc, int renderMode);

};
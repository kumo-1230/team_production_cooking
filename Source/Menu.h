#pragma once
#include "ButtonManager.h"
#include "KeyInput.h"


namespace MENU
{
	//背景あり
	const int BACK_OFF (0);
	//背景なし
	const int BACK_ON (1);
}

class Menu
{
private:
	//メニューが表示されてるか
	bool menuStart = false;
	//int menuMode = 0;
	std::unique_ptr<ButtonManager> buttonManager;
	//背景の画像
	std::unique_ptr<Sprite> sprBack;

	KeyInput keyInput;

public:
	Menu();
	~Menu();

public:
	////////////////////////////

	//ボタン追加
	void SetButton(const char* fileName, DirectX::XMFLOAT2 p, DirectX::XMFLOAT2 l, int la, int n, bool v)
	{
		buttonManager->SetButton(fileName, p, l, la, n, v);
	}

	//メニューを表示するか
	void SetMenuStart(bool S) { menuStart = S; }
	//メニューを表示してるか
	bool GetMenyuStart() { return menuStart; }
	//特定のボタンをゲット
	Button* GetButton(int i) { return buttonManager->GetButton(i); }

	////////////////////////////
public:

	void Updeat(int* hb);
	void Render(const RenderContext& rc, int renderMode);

};
#pragma once

#include "Button.h"
#include <vector>

class ButtonManager
{
private:
	//ƒ{ƒ^ƒ“‚½‚¿
	std::vector<std::unique_ptr<Button>> buttons;

public:
	ButtonManager() {};
	~ButtonManager() {};

public:
	/////////////////////////////////////////////////////

	void SetButton(const char* fileName, DirectX::XMFLOAT2 p, DirectX::XMFLOAT2 l, int la,int n,bool v);
	Button* GetButton(int i) { return buttons[i].get(); }

	/////////////////////////////////////////////////////

public:
	void Render(const RenderContext& rc);

	int HitButton();
};
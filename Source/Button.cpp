#include "Button.h"

//ポジション
//長さ
//レイヤー
//モード
//判定
Button::Button(const char* fileName, DirectX::XMFLOAT2 p, DirectX::XMFLOAT2 l, int la,int n,bool v)
{
	sprite.reset(new Sprite(fileName));
	pos = p;
	length = l;
	layer = la;
	mode = n;
	valid = v;
}

void Button::Render(const RenderContext& rc)
{
	DirectX::XMFLOAT4 c = {};
	switch (renderMode)
	{
	case BUTTON_R_MODE::NORMAL:
		c = { 1,1,1,1 };
		break;
	case BUTTON_R_MODE::HALF_INVISIBLE:
		c = { 1,1,1,0.5f };
		break;
	case BUTTON_R_MODE::INVISIBLE:
		return;
	}
	sprite->Render(rc,pos.x,pos.y,0,length.x,length.y,0,c.x,c.y,c.z,c.w);
}

//当たったか
bool Button::HitButton(const DirectX::XMFLOAT2& p, const DirectX::XMFLOAT2& le)
{
	//四角に当たっていなかったらfalse
	return !(pos.x + length.x < p.x ||
			 pos.x > p.x + le.x ||
			 pos.y + length.y < p.y ||
			 pos.y > p.y + le.y);
}

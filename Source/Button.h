#pragma once
#include "System/Sprite.h"
#include <memory>
#include <DirectXMath.h>

//レンダーモード
namespace BUTTON_R_MODE
{
	//通常
	const int NORMAL(0);
	//半透明
	const int HALF_INVISIBLE(1);
	//透明
	const int INVISIBLE(2);
}

class Button
{
private:
	//ボタンのスプライト
	std::unique_ptr<Sprite> sprite;
	//場所
	DirectX::XMFLOAT2 pos;
	//長さ
	DirectX::XMFLOAT2 length;
	//レイヤー
	int layer;
	//押したときに帰ってくる数字
	int mode;
	//判定
	bool valid;
	//レンダーモード
	int renderMode = BUTTON_R_MODE::NORMAL;
public:
	Button(const char* fileName, DirectX::XMFLOAT2 p, DirectX::XMFLOAT2 l, int la,int n,bool v);
	~Button() = default;
public:
	/////////////////////////////////////////////////////

	//秒を始める場所
	void SetPos(DirectX::XMFLOAT2 p) { pos = p; }
	//描画する画像の長さ
	void SetLength(DirectX::XMFLOAT2 l) { length = l; }
	//ボタンのレイヤー
	int GetLayer() { return layer; }
	//ヒットしたボタンが返す数値
	int GetMode() { return mode; }
	//判定を取るか設定
	void SetValid(bool i) { valid = i; }
	//今の判定モードを設定
	bool GetValid() { return valid; }
	//レンダーモード
	void SetRenderMode(int m) { renderMode = m; }

	/////////////////////////////////////////////////////

public:
	void Render(const RenderContext& rc);

	bool HitButton(const DirectX::XMFLOAT2& p,const DirectX::XMFLOAT2& le);
};
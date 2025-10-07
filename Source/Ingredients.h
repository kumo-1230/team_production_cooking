#pragma once

#include "System//Graphics.h"
#include "System/Model.h"
#include <memory>


class Ingredients
{
protected:
	std::unique_ptr<Model> model;
	DirectX::XMFLOAT3	position = { 0,0,0 };
	DirectX::XMFLOAT3	angle = { 0,0,0 };
	DirectX::XMFLOAT3	scale = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = {
		//スケールx
		1, 0, 0, 0,
		//スケールy
		0, 1, 0, 0,
		//回転
		0, 0, 1, 0,
		//位置
		0, 0, 0, 1
	};

	//半径
	float radius = 0.5f;

	//高さ
	float height = 2.0f;

	bool ChildOn = false;
public:
	Ingredients();
	~Ingredients();

	//初期化
	void Initialize();

	//終了化
	void Finalize();
private:
	//トランスフォーム更新
	void UpdateTransfom();


public:
	//更新処理
	void Update(float elapsedTime, const DirectX::XMFLOAT4X4& ParentT);

	//描画処理
	void Render(const RenderContext& rc, ModelRenderer* render);

	//デバッグ用GUI描画
	void DrawDebugGUI();

	//デバッグプリミティブ描画
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);


};
#pragma once

#include "System//Graphics.h"
#include "System/Model.h"
#include <memory>


class Ingredients
{
private:
	std::unique_ptr<Model> Model;

public:
	Ingredients();
	~Ingredients();

	//初期化
	void Initialize();

	//終了化
	void Finalize();
public:
	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(const RenderContext& rc, ModelRenderer* render);

	//デバッグ用GUI描画
	void DrawDebugGUI();

	//デバッグプリミティブ描画
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);


};
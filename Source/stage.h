#pragma once
#include "System/ModelRenderer.h"
#include <memory>
#include <vector>

class Stage
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
	//タイルモード
	int mode;

public:
	Stage();
	virtual ~Stage();

	//初期化
	virtual void Initialize() {};

protected:

	void UpdateTransform();

public:

	//更新処理
	virtual void Updeate(float elapsedTime);

	//描画処理
	virtual void Render(const RenderContext& rc, ModelRenderer* renderer);

	virtual void Event() {};

	const DirectX::XMFLOAT4X4& GetTransform() const { return transform; }
	const Model& GetModel()const { return *model.get(); }
};
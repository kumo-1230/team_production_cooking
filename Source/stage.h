#pragma once
#include "System/ModelRenderer.h"
#include "System/ShapeRenderer.h"
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
	int Lv;
	DirectX::XMFLOAT3 length = {1.0f,1.0f,1.0f};
public:
	Stage();
	virtual ~Stage();

	//初期化
	virtual void Initialize() {};

protected:

	void UpdateTransform();

public:

	///////////////////////////////////////

	const DirectX::XMFLOAT4X4& GetTransform() const { return transform; }
	const Model& GetModel()const { return *model.get(); }
	const DirectX::XMFLOAT3& GetPosition() const { return position; }
	const DirectX::XMFLOAT3& GetLength() const { return length; }
	const int GetMode() const { return mode; }
	void SetPosition(const DirectX::XMFLOAT3& p)
	{
		position = p;
		UpdateTransform();
	}
	void SetMode(int m) { mode = m; }
	const int GetLv() const { return Lv; }

	///////////////////////////////////////
public:

	//更新処理
	virtual void Update(float elapsedTime);
	//更新処理
	virtual void Update(float elapsedTime, int& x, int& y) {}

	//描画処理
	virtual void Render(const RenderContext& rc, ModelRenderer* renderer);

	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);
};
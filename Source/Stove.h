#pragma once
#include "stage.h"

class Stove : public Stage
{
public:
	Stove(const DirectX::XMFLOAT3& pos);
	~Stove() override;

	//èâä˙âª
	void Initialize() override;
public:
	///////////////////////////////////////

	void SetPosition(const DirectX::XMFLOAT3& p);
	
	///////////////////////////////////////
public:
	void Updeate(float elapsedTime) override;

	void Render(const RenderContext& rc, ModelRenderer* renderer) override;

	void Event() override;

};
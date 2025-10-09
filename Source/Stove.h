#pragma once
#include "stage.h"

class Stove : public Stage
{
private:
	int Lv;
public:
	Stove(const DirectX::XMFLOAT3& pos,int Lv);
	~Stove() override;

	//‰Šú‰»
	void Initialize() override;
public:
	///////////////////////////////////////

	
	///////////////////////////////////////
public:
	void Update(float elapsedTime) override;

	void Render(const RenderContext& rc, ModelRenderer* renderer) override;

	void Event() override;
};
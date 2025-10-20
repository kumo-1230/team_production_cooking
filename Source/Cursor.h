#pragma once
#include "stage.h"
#include "KeyInput.h"
#include "System/AudioSource.h"

class Cursor : public Stage
{
private:
	std::unique_ptr<KeyInput> key;
	float scaleC = 0.01;
	AudioSource* setUtensis = nullptr;
	int time = 0;
public:
	Cursor(const DirectX::XMFLOAT3& pos);
	~Cursor() override;
	
	//èâä˙âª
	void Initialize() override;
public:
	///////////////////////////////////////


	///////////////////////////////////////
public:
	void Update(float elapsedTime,int& x,int& y) override;

	void Render(const RenderContext& rc, ModelRenderer* renderer) override;
};
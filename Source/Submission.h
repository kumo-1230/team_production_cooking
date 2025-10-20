#pragma once
#include "Utensils.h"
#include "Ingredients.h"
#include "SceneGame.h"

class Submission : public Utensils
{
public:
	Submission(const DirectX::XMFLOAT3& pos, int lv);
	~Submission(){}
public:

	void Render(const RenderContext& rc, ModelRenderer* renderer);
};
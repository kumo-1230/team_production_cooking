#pragma once
#include "Ingredients.h"
#include "Player.h"
#include "System/Model.h"

class omurice : public Ingredients
{
public:
	omurice();
	~omurice();

public:
	void Render(const RenderContext& rc, ModelRenderer* render);
};
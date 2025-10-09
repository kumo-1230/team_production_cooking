#pragma once
#include "Ingredients.h"
#include "System/Model.h"

class Rice :public Ingredients
{
public:
	Rice();
	~Rice();
public:

	//•`‰æˆ—
	void Render(const RenderContext& rc, ModelRenderer* render);
};

class Chicken : public Ingredients
{
public:
	Chicken();
	~Chicken();
public:

	//•`‰æˆ—
	void Render(const RenderContext& rc, ModelRenderer* render);
};

class Carrot : public Ingredients
{
public:
	Carrot();
	~Carrot();
public:

	//•`‰æˆ—
	void Render(const RenderContext& rc, ModelRenderer* render);
};

class Onion : public Ingredients
{
public:
	Onion();
	~Onion();
public:

	//•`‰æˆ—
	void Render(const RenderContext& rc, ModelRenderer* render);
};

class Egg : public Ingredients
{
public:
	Egg();
	~Egg();
public:

	//•`‰æˆ—
	void Render(const RenderContext& rc, ModelRenderer* render);
};
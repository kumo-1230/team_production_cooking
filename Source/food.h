#pragma once
#include "Ingredients.h"
#include "System/Model.h"

class Rice :public Ingredients
{
private:

public:
	Rice();
	~Rice();
public:

	//•`‰æˆ—
	void Render(const RenderContext& rc, ModelRenderer* render);

	void Update() override;
};

class Chicken : public Ingredients
{
private:
public:
	Chicken();
	~Chicken();
public:

	//•`‰æˆ—
	void Render(const RenderContext& rc, ModelRenderer* render);

	void Update() override;
};

class Carrot : public Ingredients
{
private:

public:
	Carrot();
	~Carrot();
public:

	//•`‰æˆ—
	void Render(const RenderContext& rc, ModelRenderer* render);

	void Update() override;
};

class Onion : public Ingredients
{
private:

public:
	Onion();
	~Onion();
public:

	//•`‰æˆ—
	void Render(const RenderContext& rc, ModelRenderer* render);

	void Update() override;
};

class Egg : public Ingredients
{
private:

public:
	Egg();
	~Egg();
public:

	//•`‰æˆ—
	void Render(const RenderContext& rc, ModelRenderer* render);

	void Update() override;
};

class ChickenRice : public Ingredients
{
public:
	ChickenRice();
	~ChickenRice();
public:
	void Render(const RenderContext& rc, ModelRenderer* render);

	void Update() override;
};
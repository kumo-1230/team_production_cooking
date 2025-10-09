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

	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* render);
};

class Chicken : public Ingredients
{
private:
public:
	Chicken();
	~Chicken();
public:

	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* render);
};

class Carrot : public Ingredients
{
private:

public:
	Carrot();
	~Carrot();
public:

	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* render);
};

class Onion : public Ingredients
{
private:

public:
	Onion();
	~Onion();
public:

	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* render);
};

class Egg : public Ingredients
{
private:

public:
	Egg();
	~Egg();
public:

	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* render);
};
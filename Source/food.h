#pragma once
#include "Ingredients.h"
#include "System/Model.h"

class Rice :public Ingredients
{
private:
	int nowLV = 0;
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
	int nowLV = 0;
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
	int nowLV = 0;
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
	int nowLV = 0;
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
	int nowLV = 0;
public:
	Egg();
	~Egg();
public:

	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* render);
};
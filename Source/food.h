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

	void Update() override;
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

	void Update() override;
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

	void Update() override;
};

class Tomato : public Ingredients
{
public:
	Tomato();
	~Tomato();
public:
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
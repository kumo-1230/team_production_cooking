#include "food.h"

Rice::Rice()
{
	myFoodType = foodType::RICE;
	model.reset(new Model("Data/Model/kome/namagome.mdl"));
	scale.x = scale.y = scale.z = 0.1f;
	nowLV = 0;
	UpdateTransfom();
}

Rice::~Rice()
{
}


void Rice::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
}

void Rice::Update()
{	
	switch (nowLV)
	{
	case 0:
		model.reset(new Model("Data/Model/kome/namagome.mdl"));
		break;
	case 1:
		model.reset(new Model("Data/Model/kome/rice.mdl"));
		break;
	case 2:
		model.reset(new Model("Data/Model/kome/namagome.mdl"));
		break;
	}
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}


Onion::Onion()
{
	myFoodType = foodType::ONION;
	model.reset(new Model("Data/Model/Onion.mdl"));
	scale.x = scale.y = scale.z = 0.1f;
	UpdateTransfom();
}

Onion::~Onion()
{
}

void Onion::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
}

void Onion::Update()
{
	switch (nowLV)
	{
	case 0:
		model.reset(new Model("Data/Model/Onion.mdl"));
		break;
	case 1:
		model.reset(new Model("Data/Model/Onion.mdl"));
		break;
	case 2:
		model.reset(new Model("Data/Model/Onion.mdl"));
		break;
	}
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

Egg::Egg()
{
	myFoodType = foodType::EGG;
	model.reset(new Model("Data/Model/tamago.mdl"));
	scale.x = scale.y = scale.z = 0.1f;
	UpdateTransfom();
}

Egg::~Egg()
{
}

void Egg::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
}

void Egg::Update()
{

	switch (nowLV)
	{
	case 0:
		model.reset(new Model("Data/Model/tamago.mdl"));
		break;
	case 1:
		model.reset(new Model("Data/Model/tamago.mdl"));
		break;
	case 2:
		model.reset(new Model("Data/Model/tamago.mdl"));
		break;
	}

	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

ChickenRice::ChickenRice()
{
	myFoodType = foodType::CHICKENRICE;
	model.reset(new Model("Data/Model/chickenrice/chickenrice.mdl"));
	scale.x = scale.y = scale.z = 0.1f;
	nowLV = 2;
	UpdateTransfom();
}

ChickenRice::~ChickenRice()
{
}

void ChickenRice::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
}

void ChickenRice::Update()
{
	switch (nowLV)
	{
	case 0:
		model.reset(new Model("Data/Model/chickenrice/chickenrice.mdl"));
		break;
	case 1:
		model.reset(new Model("Data/Model/chickenrice/chickenrice.mdl"));
		break;
	case 2:
		model.reset(new Model("Data/Model/chickenrice/chickenrice.mdl"));
		break;
	}
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

Tomato::Tomato()
{
	myFoodType = foodType::TOMATO;
	model.reset(new Model("Data/Model/tomato/tomato.mdl"));
	scale.x = scale.y = scale.z = 1.0f;
	nowLV = 2;
	UpdateTransfom();
}

Tomato::~Tomato()
{
}

void Tomato::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
}

void Tomato::Update()
{
	switch (nowLV)
	{
	case 0:
		model.reset(new Model("Data/Model/tomato/tomato.mdl"));
		break;
	case 1:
		model.reset(new Model("Data/Model/tomato/cut_tomato.mdl"));
		break;
	case 2:
		model.reset(new Model("Data/Model/tomato/tomato_sauce.mdl"));
		break;
	}
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

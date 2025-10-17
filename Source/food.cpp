#include "food.h"

Rice::Rice()
{
	myFoodType = foodType::RICE;
	models[0] = std::make_unique<Model>("Data/Model/kome/namagome.mdl");
	models[1] = std::make_unique<Model>("Data/Model/kome/rice.mdl");
	models[2] = std::make_unique<Model>("Data/Model/kome/namagome.mdl");
	
	scale.x = scale.y = scale.z = 0.1f;
	nowLV = 1;
	UpdateTransfom();
}

Rice::~Rice()
{
}


void Rice::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model, ShaderId::Lambert);
}

void Rice::Update()
{	
	model = models[nowLV].get();
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}


Onion::Onion()
{
	models[0] = std::make_unique<Model>("Data/Model/Onion.mdl");
	models[1] = std::make_unique<Model>("Data/Model/Onion.mdl");
	models[2] = std::make_unique<Model>("Data/Model/Onion.mdl");
	myFoodType = foodType::ONION;
	scale.x = scale.y = scale.z = 0.1f;
	UpdateTransfom();
}

Onion::~Onion()
{
}

void Onion::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model, ShaderId::Lambert);
}

void Onion::Update()
{
	model = models[nowLV].get();
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

Egg::Egg()
{
	models[0] = std::make_unique<Model>("Data/Model/egg/tamago.mdl");
	models[1] = std::make_unique<Model>("Data/Model/egg/yakitamago.mdl");
	models[2] = std::make_unique<Model>("Data/Model/egg/yakitamago.mdl");
	myFoodType = foodType::EGG;
	scale.x = scale.y = scale.z = 0.1f;
	nowLV = 1;
	UpdateTransfom();
}

Egg::~Egg()
{
}

void Egg::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model, ShaderId::Lambert);
}

void Egg::Update()
{
	model = models[nowLV].get();
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

ChickenRice::ChickenRice()
{
	myFoodType = foodType::CHICKENRICE;
	scale.x = scale.y = scale.z = 0.1f;
	models[0] = std::make_unique<Model>("Data/Model/chickenrice/chickenrice.mdl");
	models[1] = std::make_unique<Model>("Data/Model/chickenrice/rice.mdl");
	models[2] = std::make_unique<Model>("Data/Model/chickenrice/chickenriceWithOnion.mdl");
	nowLV = 2;
	UpdateTransfom();
}

ChickenRice::~ChickenRice()
{
}

void ChickenRice::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model, ShaderId::Lambert);
}

void ChickenRice::Update()
{
	model = models[nowLV].get();
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

Tomato::Tomato()
{
	myFoodType = foodType::TOMATO;
	models[0] = std::make_unique<Model>("Data/Model/tomato/tomato.mdl");
	models[1] = std::make_unique<Model>("Data/Model/tomato/cut_tomato.mdl");
	models[2] = std::make_unique<Model>("Data/Model/tomato/tomato_sauce.mdl");
	scale.x = scale.y = scale.z = 1.0f;
	nowLV = 2;
	UpdateTransfom();
}

Tomato::~Tomato()
{
}

void Tomato::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model, ShaderId::Lambert);
}

void Tomato::Update()
{
	model = models[nowLV].get();
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

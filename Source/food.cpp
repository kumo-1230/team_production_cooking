#include "food.h"

Rice::Rice()
{
	myFoodType = foodType::RICE;
	model.reset(new Model("Data/Model/namagome.mdl"));
	scale.x = scale.y = scale.z = 0.1f;
	nowLV = 1;
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
		model.reset(new Model("Data/Model/namagome.mdl"));
		break;
	case 1:
		model.reset(new Model("Data/Model/namagome.mdl"));
		break;
	case 2:
		model.reset(new Model("Data/Model/namagome.mdl"));
		break;
	}
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

Chicken::Chicken()
{
	myFoodType = foodType::CHICKING;
	model.reset(new Model("Data/Model/SpikeBall/SpikeBall.mdl"));
	scale.x = scale.y = scale.z = 0.1f;
	UpdateTransfom();
}

Chicken::~Chicken()
{
	

}

void Chicken::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
}

void Chicken::Update()
{
	switch (nowLV)
	{
	case 0:
		model.reset(new Model("Data/Model/SpikeBall/SpikeBall.mdl"));
		break;
	case 1:
		model.reset(new Model("Data/Model/SpikeBall/SpikeBall.mdl"));
		break;
	case 2:
		model.reset(new Model("Data/Model/SpikeBall/SpikeBall.mdl"));
		break;
	}
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

Carrot::Carrot()
{
	myFoodType = foodType::CARROT;
	model.reset(new Model("Data/Model/Sword/Sword.mdl"));
	scale.x = scale.y = scale.z = 0.1f;
	UpdateTransfom();
}

Carrot::~Carrot()
{
}

void Carrot::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
}

void Carrot::Update()
{
	switch (nowLV)
	{
	case 0:
		model.reset(new Model("Data/Model/Sword/Sword.mdl"));
		break;
	case 1:
		model.reset(new Model("Data/Model/Sword/Sword.mdl"));
		break;
	case 2:
		model.reset(new Model("Data/Model/Sword/Sword.mdl"));
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
	nowLV = 1;
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
	model.reset(new Model("Data/Model/gasukonro.mdl"));
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
		model.reset(new Model("Data/Model/gasukonro.mdl"));
		break;
	case 1:
		model.reset(new Model("Data/Model/gasukonro.mdl"));
		break;
	case 2:
		model.reset(new Model("Data/Model/gasukonro.mdl"));
		break;
	}
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

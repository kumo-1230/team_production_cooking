#include "food.h"

Rice::Rice()
{
	myFoodType = foodType::RICE;
	model.reset(new Model("Data/Model/onion.mdl"));
	scale.x = scale.y = scale.z = 0.1f;
	UpdateTransfom();
}

Rice::~Rice()
{
}

void Rice::Render(const RenderContext& rc, ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
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

Carrot::Carrot()
{
	myFoodType = foodType::RICE;
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

Onion::Onion()
{
	myFoodType = foodType::RICE;
	model.reset(new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl"));
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

Egg::Egg()
{
	myFoodType = foodType::RICE;
	model.reset(new Model("Data/Model/Stage/ExampleStage.mdl"));
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

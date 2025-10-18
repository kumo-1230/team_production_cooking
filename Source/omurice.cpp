#include "omurice.h"

omurice::omurice()
{
	models[0] = std::make_unique<Model>("Data/Model/omu/omu.mdl");
	models[1] = std::make_unique<Model>("Data/Model/omusouce/omusauce.mdl");
	models[2] = std::make_unique<Model>("Data/Model/omudemi/omudemi.mdl");
	models[3] = std::make_unique<Model>("Data/Model/omuwhite/omuwhite.mdl");
	scale.x = scale.y = scale.z = 0.1f;
	myFoodType = foodType::OMURICE;
	nowLV = 2;
	omuType = 0;
	model = models[omuType].get();
}

omurice::~omurice()
{
}

void omurice::Render(const RenderContext& rc,  ModelRenderer* render)
{
	render->Render(rc, transform, model, ShaderId::Lambert);
}

void omurice::Update()
{
	model = models[omuType].get();
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

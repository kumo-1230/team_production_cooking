#include "omurice.h"

omurice::omurice()
{
	model.reset(new Model("Data/Model/omu/omu.mdl"));
	scale.x = scale.y = scale.z = 0.1f;
	myFoodType = foodType::OMURICE;
	nowLV = 2;
}

omurice::~omurice()
{
}

void omurice::Render(const RenderContext& rc,  ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
}

void omurice::Update()
{
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

#include "omurice.h"

omurice::omurice()
{
	model.reset(new Model("Data/Model/omu/omu.mdl"));
	scale.x = scale.y = scale.z = 0.1f;
	myFoodType = foodType::OMURICE;
	nowLV = 2;
	omuType = 1;
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
	switch (omuType)
	{
	case 0:
		model.reset(new Model("Data/Model/omu/omu.mdl"));
		break;
	case 1:
		model.reset(new Model("Data/Model/omu/omu.mdl"));
		break;
	case 2:
		model.reset(new Model("Data/Model/omu/omu.mdl"));
		break;
	case 3:
		model.reset(new Model("Data/Model/omu/omu.mdl"));
		break;
	}
	UpdateTransfom();
	//モデル行列更新
	model->UpdateTransform();
}

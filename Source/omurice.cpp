#include "omurice.h"

omurice::omurice()
{
	model.reset(new Model("Data/Model/omu.mdl"));
	scale.x = scale.y = scale.z = 0.1f;
}

omurice::~omurice()
{
}

void omurice::Render(const RenderContext& rc,  ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
}
#include "Submission.h"

Submission::Submission(const DirectX::XMFLOAT3& pos, int lv)
{
	position = pos;
	scale.x = scale.y = scale.z = 0.1f;
	angle = { 0,DirectX::XMConvertToRadians(270),0 };
	model = std::make_unique<Model>("Data/Model/Utensils/Submission/subission.mdl");
	UpdateTransform();
	mode = 4;
}

int Submission::submit(Ingredients* ing,Dish* dish,FoodManager* foodManager)
{
	foodManager->RemoveFood(ing);
	dish->setLv(2);
	return 500;
}

void Submission::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model.get(), ShaderId::Lambert);
}
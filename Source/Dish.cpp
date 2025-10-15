#include "Dish.h"
#include "omurice.h"
#include "System/ImGuiRenderer.h"
#include <imgui.h>

#define DEBUG

Dish::Dish()
{
	model.reset(new Model("Data/Model/Plate.mdl"));
	scale.x =scale.y = scale.z = 0.1f;
	dishLV = 0;
	//���V�s�������Ă����܂�(set���g�����Ƃŏ��Ԃ𖳎�)
	recipes = {
	{ {foodType::EGG,foodType::CHICKENRICE},foodType::OMURICE }
	};

}

Dish::~Dish()
{
}

Ingredients* Dish::MixDishOnFood(Ingredients* otherIng,FoodManager* foodmanager)
{
	if (!otherIng)return nullptr;
	//�H�ނ��M�̏�ō������킹�鏈��
	if (OnDishFood)
	{
		std::set<foodType> recipe = {static_cast <foodType>(OnDishFood->GetType()),static_cast<foodType>(otherIng->GetType()) };
		auto it = recipes.find(recipe);
		if (it != recipes.end()) //���V�s������������
		{
			if (OnDishFood->GetLv() == 2 && otherIng->GetLv() == 2)
			{
				//��������
				auto newFood = std::make_unique<omurice>();
				newFood->setScale(scale);
				newFood->setPosition(position);

				Ingredients* ing = newFood.get();
				//�Â��̏����ĐV�����̓����
				foodmanager->RemoveFood(OnDishFood);
				foodmanager->RemoveFood(otherIng);
				foodmanager->Register(std::move(newFood));
				//OnDishFood = nullptr;
				return ing;
			}
		}
	}
	return OnDishFood;
}

void Dish::Render(const RenderContext& rc,ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
#ifdef DEBUG
	//�Ȃ񂩂̃|�W�V����������Ă���
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	//�\���ꏊ
	ImGui::SetNextWindowPos(ImVec2(pos.x + 100, pos.y + 100), ImGuiCond_Once);
	//�傫��
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Dish", nullptr, ImGuiWindowFlags_None))
	{
		//�g�����X�t�H�[��
		//if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::InputFloat3("pos", &position.x);
			ImGui::InputInt("Lv", &dishLV);

		}
	}
	ImGui::End();

#endif // DEBUG

}

void Dish::Update(float elapsedTime)
{
	UpdateTransfom();
	//���f���s��X�V
	model->UpdateTransform();
}

void Dish::UpdateTransfom()
{
	//�X�P�[���s�񐧍�
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	//��]�s��𐧍�
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	//�ʒu�s����쐬
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//�O�̍s���g�ݍ��킹�ă��[���h�s����쐬
	DirectX::XMMATRIX W = S * R * T;

	//�v�Z�������[���h�s������o��
	DirectX::XMStoreFloat4x4(&transform, W);
}

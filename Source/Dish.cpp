#include "Dish.h"
#include "omurice.h"


Dish::Dish()
{
	model.reset(new Model("Data/Model/Slime/Slime.mdl"));
	scale.x = scale.y = scale.z = 0.01f;

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

				OnDishFood = nullptr;
				return ing;
			}
		}
	}
	return otherIng;
}

void Dish::Render(const RenderContext& rc,ModelRenderer* render)
{
	render->Render(rc, transform, model.get(), ShaderId::Lambert);
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

#include "Sink.h"

//�v���C���[���ŃV���N��G�����Ƃ��Ƀ��C�g���I�����ǂ������f���ăI�t�������ꍇ�ׂ̃V���N�̃|�W�V�������Q�b�g����
//����̃v���O�������Q�Ƃł���悤�ɂ�����@���l����

//Update���񂷂Ƃ���Sink&&R = ture�̎��ЂƂO�̃V���N�̃|�C���^��get���Ĉ����Ƃ��Ă킽����Set�֐��ŎM��n��
//�M�N���X���ł�����ǉ�

Sink::Sink(const DirectX::XMFLOAT3& pos, int lv,bool R)
{
	right = R;
	Lv = lv;
	if (Lv == 0)
	{
		if (right)
		{
			model = std::make_unique<Model>("Data/Model/sinkLv1_1.mdl");
		}
		else
		{
			model = std::make_unique<Model>("Data/Model/sinkLv1_2.mdl");
		}
	}
	if (Lv == 1)
	{
		if (right)
		{
			model = std::make_unique<Model>("Data/Model/sinkLv2_1.mdl");
		}
		else
		{
			model = std::make_unique<Model>("Data/Model/sinkLv2_2.mdl");
		}
	}
	if (Lv == 2)
	{
		if (right)
		{
			model = std::make_unique<Model>("Data/Model/sinkLv1_1.mdl");
		}
		else
		{
			model = std::make_unique<Model>("Data/Model/sinkLv1_2.mdl");
		}
	}
	if (Lv == 2)
	{
		Lv = 3;
	}
	position = pos;
	scale = { 0.1f,0.1f,0.1f };
	UpdateTransform();
	cookingTimerBank = cookingTimer;
}

Sink::~Sink()
{
}

void Sink::Update(float elapsedTime)
{
	Utensils::Update(elapsedTime);
	dishCount = oldDish.size() - 1;
	if (cookingTimer <= 0 && right && dishCount > -1)
	{
		//�����Ő􂢏I������M��move�֐��ňړ�
		newDish.push_back(std::move(oldDish[dishCount]));
		int newDishCount = newDish.size() - 1;
		DirectX::XMFLOAT3 p = { friendX * 2.0f,2.0f,friendY * 2.0f };
		p.y += 0.5f * newDishCount;
		//�M�̃Z�b�g�|�W�V�����������Őݒ�&���x����1�ɖ߂�
		newDish[newDishCount]->setPosition(p);
		newDish[newDishCount]->setLv(1);
		cookingTimer = cookingTimerBank;
	}
}
void Sink::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	Utensils::Render(rc,renderer);
	if (newDish.size() != 0)
	{
		for (const auto& d : newDish)
		{
			//�M�̃����_�[
			d->Render(rc, renderer);
		}
	}
}

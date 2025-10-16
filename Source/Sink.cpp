#include "Sink.h"
#include "Player.h"

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
	cookingTimer = timer[Lv];
	position = pos;
	scale = { 0.1f,0.1f,0.1f };
	UpdateTransform();
	cookingTimerBank = cookingTimer;
}

Sink::~Sink()
{
}

void Sink::Update(float elapsedTime, DishManager* DM, Player* P)
{
	if (dishCount > 0)
	{
		cookingTimer -= 1 * elapsedTime;
	}
	for (int i = 0; i < DM->getDishNum(); i++)
	{
		if (DM->getDish(i) == P->getDish() && DM->getDish(i)->GetDishLV() == 1)
		{
			DM->getDish(i)->SetIsSink(true);
			P->SetDish(nullptr);
			DirectX::XMFLOAT3 p = {position.x,position.y - 1,position.z};
			DM->getDish(i)->setPosition(p);
			dishCount++;
		}
	}
	if (cookingTimer <= 0 && right)
	{
		//�����Ő􂢏I������M��move�֐��ňړ�
		for (int i = 0; i < DM->getDishNum(); i++)
		{
			if (DM->getDish(i)->GetIsSink() && DM->getDish(i)->GetLv() == 1)
			{
				DirectX::XMFLOAT3 p = { friendX * 2.0f,2.0f,friendY * 2.0f };
				p.y += 0.5f;
				DM->getDish(i)->setPosition(p);
				DM->getDish(i)->setLv(0);
				DM->getDish(i)->SetIsSink(false);
				cookingTimer = cookingTimerBank;
			}
		}
	}
}
void Sink::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	Utensils::Render(rc,renderer);
}

#include "Sink.h"

//プレイヤー側でシンクを触ったときにライトがオンかどうか判断してオフだった場合隣のシンクのポジションをゲットして
//それのプログラムを参照できるようにする方法を考える

//Updateを回すときにSink&&R = tureの時ひとつ前のシンクのポインタをgetして引数としてわたしてSet関数で皿を渡す
//皿クラスができたら追加

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

void Sink::Update(float elapsedTime, DishManager* DM)
{
	Utensils::Update(elapsedTime);
	if (cookingTimer <= 0 && right)
	{
		//ここで洗い終わった皿をmove関数で移動
		for (int i = 0; i < DM->getDishNum(); i++)
		{
			if (DM->getDish(i)->GetIsSink() && DM->getDish(i)->GetLv() == 1)
			{
				DirectX::XMFLOAT3 p = { friendX * 2.0f,2.0f,friendY * 2.0f };
				p.y += 0.5f;
				DM->getDish(i)->setPosition(p);
				DM->getDish(i)->setLv(0);
				cookingTimer = cookingTimerBank;
			}
		}
	}
}
void Sink::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	Utensils::Render(rc,renderer);
}

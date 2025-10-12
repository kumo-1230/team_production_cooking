#include "Sink.h"

//プレイヤー側でシンクを触ったときにライトがオンかどうか判断してオフだった場合隣のシンクのポジションをゲットして
//それのプログラムを参照できるようにする方法を考える

//Updateを回すときにSink&&R = tureの時ひとつ前のシンクのポインタをgetして引数としてわたしてSet関数で皿を渡す
//皿クラスができたら追加

Sink::Sink(const DirectX::XMFLOAT3& pos, int lv,bool R)
{
	right = R;
	model = std::make_unique<Model>("Data/Model/gasukonro.mdl");
	Lv = lv;
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
		//ここで洗い終わった皿をmove関数で移動
		newDish.push_back(oldDish[dishCount]);
		int newDishCount = newDish.size() - 1;
		DirectX::XMFLOAT3 p = { friendX * 2.0f,2.0f,friendY * 2.0f };
		p.y += 0.5f * newDishCount;
		//皿のセットポジションをここで設定&レベルを1に戻す

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
			//皿のレンダー

		}
	}
}

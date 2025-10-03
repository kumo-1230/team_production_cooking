#pragma once
#include "Weapon.h"
#include <vector>

class WeaponManager
{
private:

	struct WeaponBild
	{
		//作る数
		int makeCount = 0;
		//何の武器か
		int AllWeaponMode;
		//武器のレベル
		int AllWeaponLv;
		//必要コスト
		int cost = 1;
	};

	//今回使ったコスト
	int nowAllCost = 0;
	//前回使ったコスト
	int oldAllCost = 0;
	//今回使えるSP
	int allSP = 4;

	std::vector<WeaponBild> nowWeaponBild;
	std::vector<WeaponBild> oldWeaponBild;

	std::vector<std::unique_ptr<Weapon>> weapons;
public:
	WeaponManager();
	~WeaponManager();

public:

	//////////////////////////////

	//ウェポンの種類
	void SetWeaponBild(int weaponMode,int addLv);
	//武器を作る
	void SetWeapon();
	//武器のレベル
	int GetLv(int weaponMode);
	//コストを足す
	void AddCost(int weaponMode,int addCost);
	//必要コスト
	int GetCost(int weaponMode);
	//使えるSP
	int GetAllSP() { return allSP; }
	//使えるSPを増やす
	void ChangeSP(int addSp);

	//指定したモードのウェポンを返す
	Weapon* GetWeapon(int weaponMode);

	//指定したインデックスのウェポンを返す
	Weapon* GetWeaponIndex(int index) { return weapons.at(index).get(); }

	//ウェポンの数
	int GetWeaponCount() { return static_cast<int>(weapons.size()); }

	//////////////////////////////

public:

	void Update(float el, const Player& p, const EnemyManager& em,const Enemy& e, int lanchChar);

	void Render(const RenderContext& rc, ModelRenderer* renderer);
};

#pragma once
#include "Weapon.h"
#include <vector>

class WeaponManager
{
private:

	struct WeaponBild
	{
		//��鐔
		int makeCount = 0;
		//���̕��킩
		int AllWeaponMode;
		//����̃��x��
		int AllWeaponLv;
		//�K�v�R�X�g
		int cost = 1;
	};

	//����g�����R�X�g
	int nowAllCost = 0;
	//�O��g�����R�X�g
	int oldAllCost = 0;
	//����g����SP
	int allSP = 4;

	std::vector<WeaponBild> nowWeaponBild;
	std::vector<WeaponBild> oldWeaponBild;

	std::vector<std::unique_ptr<Weapon>> weapons;
public:
	WeaponManager();
	~WeaponManager();

public:

	//////////////////////////////

	//�E�F�|���̎��
	void SetWeaponBild(int weaponMode,int addLv);
	//��������
	void SetWeapon();
	//����̃��x��
	int GetLv(int weaponMode);
	//�R�X�g�𑫂�
	void AddCost(int weaponMode,int addCost);
	//�K�v�R�X�g
	int GetCost(int weaponMode);
	//�g����SP
	int GetAllSP() { return allSP; }
	//�g����SP�𑝂₷
	void ChangeSP(int addSp);

	//�w�肵�����[�h�̃E�F�|����Ԃ�
	Weapon* GetWeapon(int weaponMode);

	//�w�肵���C���f�b�N�X�̃E�F�|����Ԃ�
	Weapon* GetWeaponIndex(int index) { return weapons.at(index).get(); }

	//�E�F�|���̐�
	int GetWeaponCount() { return static_cast<int>(weapons.size()); }

	//////////////////////////////

public:

	void Update(float el, const Player& p, const EnemyManager& em,const Enemy& e, int lanchChar);

	void Render(const RenderContext& rc, ModelRenderer* renderer);
};

#include "WeaponManager.h"
#include "Player.h"
#include "Enemy.h"

WeaponManager::WeaponManager()
{
}

WeaponManager::~WeaponManager()
{
}

//����̃r���h�ݒ�
void WeaponManager::SetWeaponBild(int weaponMode, int addLv)
{
	bool ch;
	for (int i = 0; i < addLv; i++)
	{
		ch = false;
		if (nowWeaponBild.size() == 0)
		{
			nowWeaponBild.push_back({ 1,weaponMode,1 });
			continue;
		}
		for (auto& w : nowWeaponBild)
		{
			if (w.AllWeaponMode == weaponMode)
			{
				w.AllWeaponLv++;
				if (w.AllWeaponLv % 2 == 0)w.makeCount++;
				ch = true;
			}
		}
		if (ch == false)
		{
			nowWeaponBild.push_back({ 1,weaponMode,1 });
		}
	}
	return;
}

//�r���h�쐬
void WeaponManager::SetWeapon()
{
	weapons.clear();
	//���퐧��
	for (auto& w : nowWeaponBild)
	{
		for (int i = 0; i < w.makeCount; i++)
		{
			switch (w.AllWeaponMode)
			{
				//�܂��������
			case WEAPON::BULLET_STRAIGHT:
				break;
				//�z�[�~���O
			case WEAPON::BULLET_HOMING:
				break;
				//�����̎�������
			case WEAPON::ROTATION:
				break;
				//�����_������
			case WEAPON::BULLET_RANDOM:
				break;
				//�\�ꌕ
			case WEAPON::SWORD:
				
				break;
				//�u�[������
			case WEAPON::BOOMERANG:
				
				break;
				//���~��
			case WEAPON::STOP:
				
				break;
			}
		}
		nowAllCost += w.cost;
	}

	//����̃r���h��ۑ�
	for (auto& i : nowWeaponBild)
	{
		oldWeaponBild.push_back(i);
	}
	//����g�����R�X�g��ۑ�
	oldAllCost = nowAllCost;
	nowAllCost = 0;
	nowWeaponBild.clear();
}

int WeaponManager::GetLv(int weaponMode)
{
	for (auto& w : nowWeaponBild)
	{
		if (w.AllWeaponMode == weaponMode) return w.AllWeaponLv;
	}
	return 0;
}

void WeaponManager::AddCost(int weaponMode, int addCost)
{
	for (auto& w : nowWeaponBild)
	{
		if (w.AllWeaponMode == weaponMode)
		{
			w.cost += addCost;
		}
	}
}

int WeaponManager::GetCost(int weaponMode)
{
	for (auto& w : nowWeaponBild)
	{
		if (w.AllWeaponMode == weaponMode) return w.cost;
	}
	return 0;
}

void WeaponManager::ChangeSP(int addSp)
{
	allSP += addSp;
}

Weapon* WeaponManager::GetWeapon(int weaponMode)
{
	for (auto& i : weapons)
	{
		if (i->GetWeaponMode() == weaponMode)
		{
			return i.get();
		}
	}
	return nullptr;
}

void WeaponManager::Update(float el, const Player& p, const EnemyManager& em, const Enemy& e, int lanchChar)
{
	for (auto& i : weapons)
	{

		{
			if (i->GetStart() == 0)
			{
				i->Launch(p, em,e,lanchChar);
				i->AddStart();
			}
			if (i->GetWeaponMode() == WEAPON::ROTATION)
			{
				DirectX::XMFLOAT3 pos;
				if (lanchChar == LCHAR::PLAYER)
				{
					pos = p.GetPosition();
					pos.y = p.GetHeight() * 0.5f;
				}
				else if (lanchChar == LCHAR::ENEMY)
				{
					pos = e.GetPosition();
					pos.y = e.GetHeight() * 0.5f;
				}
				i->Update(el, pos);
			}
			else
			{
				i->Update(el);
			}
		}
		if (i->GetInvisibule() == true) 
		{
			i->CoolTimeDown(el);
			if (i->GetCoolTime() < 0.0f)
			{
				i->Launch(p, em,e,lanchChar);
				i->SetInvisibule();
			}
		}
	}
}

void WeaponManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	for (auto& i : weapons)
	{
		if (i->GetInvisibule() == false)
		{
			i->Render(rc, renderer);
		}
	}
}

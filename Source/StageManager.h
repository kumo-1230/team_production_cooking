#pragma once
#include "stage.h"
#include "Stove.h"
#include "KeyInput.h"
#include "Utensils.h"
#include "System/Sprite.h"
#include "foodManager.h"

class Player;


class StageManager
{
public:
	enum TILE_MODEL
	{
		NONE = 0,
		BACON,      //�x�[�R��
		CABBAGE,    //�L���x�c
		EGG,        //��
		OFFER,      //��
		RETURN_DISH,//�M���Ԃ��Ă���Ƃ�
		ONION,      //�ʂ˂�
		POTATO,     //�|�e�g
		RICE,       //��
		TOMATO,     //�g�}�g

		            //�ݒu�\
		BOARD,      //�܂Ȕ�
		POT,        //��
		SINK,       //�V���N
		STOVE,      //�X�g�[�u
		TABLE,      //�e�[�u��
		BOX,        //�H�ރ{�b�N�X

		            //�\�[�X
		KETCHUP,    //�P�`���b�v
		DEMI,       //�f�~�O���X
		WHITE,      //�z���C�g�\�[�X
		PLAYER,		//�X�z�[���ʒu
	};
private:
	//��
	std::unique_ptr<Stage> floor;//��
	//�^�C���}�b�v
	std::vector<std::unique_ptr<Stage>> tileMapBox;//�H�ރ{�b�N�X
	std::vector<std::unique_ptr<Utensils>> tileMapUtensils;//�������
	std::unique_ptr<Stage> cursor;//�u���ꏊ
	std::unique_ptr<KeyInput> key;//�C���v�b�g
	std::vector<std::vector<std::unique_ptr<Utensils>>> TileMapBank;//�}�b�v�\�z���̕ۑ��ꏊ
	int x = 0,//����X
		y = 0,//����Y
		TileMode = 0,//���̃��[�h
		Lv = 0;//���̃��x��
	int range;
	bool Long = false;
	int nextX = 0,//�j�}�X�̎��ׂ̗�X
		nextY = 0;//�j�}�X�̎��ׂ̗�Y
	int oldX = -1,//��O��X
		oldY = -1,//��O��Y
		oldTileMode = -1,//��O�̃��[�h
		oldLv = -1;//��O�̃��x��
	bool build = true;//�r���h���I�������
	int subtractionMoney = 0;//�ŏI�I�Ɉ�����邨��

	const int ADD_MONEY[3] = { 3000,4000,5000 };

	std::unique_ptr<Sprite> sprite;
	std::unique_ptr<Sprite> spriteWarning;

	//�v���C���[���X�|�[������ꏊ�̃C���f�b�N�X��ۑ�
	int PlayerPos{-1};

	int timerCount{0};

	bool A = true;//�s�����x



	std::unique_ptr<Sprite> spritePlus;
	std::unique_ptr<Sprite> spriteNo;
	std::unique_ptr<Sprite> spriteMinus;
	std::unique_ptr<Sprite> spriteMiss;

	float renderPosX;
	float renderPosY;

	float timer;

	bool TipRenderPlus;
	bool TipRenderNo;
	bool TipRenderMiss;
	bool TipRenderMinus;

public:
	StageManager();
	~StageManager();

	void Initialize();
public:
	////////////////////////////////////////////

	//���Q�b�g
	const Stage* GetFloor() const { return floor.get(); }
	//�H��Box�Q�b�g
	const Stage* GetTileMapBox(int i) const { return tileMapBox[i].get(); }
	//�����邩
	const int GetTileMapBoxLength() const { return tileMapBox.size();}
	//�ꏊ
	const DirectX::XMFLOAT3& GetBoxPosition(int i) const { return tileMapBox[i]->GetPosition(); }
	//����
	const DirectX::XMFLOAT3& GetBoxLength(int i) const { return tileMapBox[i]->GetLength(); }

	//�������
	const Utensils* GetTileMapUtensils(int i) const { return tileMapUtensils[i].get(); }
	//�������̗�
	const int GetTileMapUtensilsLength() const { return tileMapUtensils.size();}
	//�ꏊ
	const DirectX::XMFLOAT3& GetUtensilsPosition(int i) const { return tileMapUtensils[i]->GetPosition(); }
	//����
	const DirectX::XMFLOAT3& GetUtensilsLength(int i) const { return tileMapUtensils[i]->GetLength(); }

	//�^�C���}�b�v�ɃZ�b�g����
	void SetMapTip();
	//�������̂���
	const int GetMoney() const { return subtractionMoney; }

	void SetBuild(bool b) {
		build = b;
	}

	////////////////////////////////////////////

public:

	void Update(float elapsedTime, DishManager* DM, Player* P,FoodManager* F);
	void Render(const RenderContext& rc, ModelRenderer* renderer);
	void Render2D(const RenderContext& rc);
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	void BuildingMap();

};
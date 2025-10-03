#pragma once

#include "System/Sprite.h"
#include "Scene.h"
#include "Menu.h"

enum PwUp
{
	//�߂�
	RETURN = 0,
	//���i�グ��
	STRING_UP,
	//���i������
	STRING_DOWN,
	//�z�[�~���O�グ��
	HOMING_UP,
	//�z�[�~���O������
	HOMING_DOWN,
	//��]�グ��
	ROTATE_UP,
	//��]������
	ROTATE_DOWN,
};

const int addCost[3][5] =
{
	{1,2,3,4,5},
	{1,2,3,4,5},
	{1,2,3,4,5},
};

//�^�C�g���V�[��
class SceneTitle : public Scene
{
private:
	std::unique_ptr<Sprite> sprite;
	std::unique_ptr<Sprite> straight;
	std::unique_ptr<Sprite> homing;
	std::unique_ptr<Sprite> rotate;

	std::unique_ptr<Menu> titleStartMenu;
	std::unique_ptr<Menu> titlePwUpMenu;
	int pwUpMode;
public:
	SceneTitle();
	~SceneTitle() override{}

	void CostChange(int pwMode,bool Up);
	bool PwJudge(int pwMode, bool Up);

	//������
	void Initialize() override;

	//�I����
	void Finalize() override;

	//�X�V����
	void Update(float elapsedTime) override;

	void PwUp(int pwMode,bool Up);

	//�`�揈��
	void Render() override;

	//GUI�`��
	void DrawGUI() override;
};
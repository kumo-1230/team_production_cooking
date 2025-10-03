#pragma once

#include "Scene.h"

//�V�[���}�l�[�W���[
class SceneManager
{
private:
	Scene* currrentScene = nullptr;
	Scene* nextScene = nullptr;

public:
	SceneManager() {}
	~SceneManager() {}

public:
	//�V���O���g��
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render();

	//GUI�`��
	void DrawGUI();

	//�V�[���N���A
	void Clear();

	//�V�[���؂�ւ�
	void ChangeScene(Scene* scene);
};

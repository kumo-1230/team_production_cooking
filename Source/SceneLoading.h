#pragma once

#include "System/Sprite.h"
#include "Scene.h"

#include <thread>

//���[�f�B���O
class SceneLoading : public Scene
{
private:
	Sprite* sprite = nullptr;
	float angle = 0.0f;
	Scene* nextScene = nullptr;

	std::thread* thread = nullptr;

private:
	//���[�f�B���O�X���b�h
	static void LoadingThread(SceneLoading* scene);

public:
	//SceneLoading(){}
	SceneLoading(Scene* nexetScene): nextScene(nexetScene){}
	~SceneLoading() override {}

	//������
	void Initialize() override;

	//�I����
	void Finalize() override;

	//�X�V����
	void Update(float elapsedTime) override;

	//�`�揈��
	void Render() override;

	//GUI�`��
	void DrawGUI() override;
};
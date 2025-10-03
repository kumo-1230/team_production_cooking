#include "SceneManager.h"

void SceneManager::Update(float elapsedTime)
{
	if (nextScene != nullptr)
	{
		//�I��
		Clear();

		//�V�����V�[���ݒ�
		currrentScene = nextScene;
		nextScene = nullptr;

		//������
		if (currrentScene->IsReady() == false)
		{
			currrentScene->Initialize();
		}
	}

	if (currrentScene != nullptr)
	{
		currrentScene->Update(elapsedTime);
	}

}

void SceneManager::Render()
{
	if (currrentScene != nullptr)
	{
		currrentScene->Render();
	}
}

void SceneManager::DrawGUI()
{
	if (currrentScene != nullptr)
	{
		currrentScene->DrawGUI();
	}
}

void SceneManager::Clear()
{
	if (currrentScene != nullptr)
	{
		currrentScene->Finalize();
		delete currrentScene;
		currrentScene = nullptr;
	}
}

//�V�[���؂�ւ�
void SceneManager::ChangeScene(Scene* scene)
{
	nextScene = scene;
}

#pragma once

#include "Scene.h"

class SceneResult : public Scene
{
private:
	int gameTimer;

public:
	SceneResult();
	~SceneResult() = default;

	void Update(float elapsedTime) override;

	void Render() override;

	//������
	void Initialize()override {};

	//�I����
	void Finalize()override {};

	//GUI�`��
	void DrawGUI()override {};
};
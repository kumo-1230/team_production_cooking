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

	//‰Šú‰»
	void Initialize()override {};

	//I—¹‰»
	void Finalize()override {};

	//GUI•`‰æ
	void DrawGUI()override {};
};
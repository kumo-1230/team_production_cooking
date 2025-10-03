#pragma once

#include "System/Sprite.h"
#include "Scene.h"
#include "Menu.h"

enum PwUp
{
	//戻る
	RETURN = 0,
	//直進上げる
	STRING_UP,
	//直進下げる
	STRING_DOWN,
	//ホーミング上げる
	HOMING_UP,
	//ホーミング下げる
	HOMING_DOWN,
	//回転上げる
	ROTATE_UP,
	//回転下げる
	ROTATE_DOWN,
};

const int addCost[3][5] =
{
	{1,2,3,4,5},
	{1,2,3,4,5},
	{1,2,3,4,5},
};

//タイトルシーン
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

	//初期化
	void Initialize() override;

	//終了化
	void Finalize() override;

	//更新処理
	void Update(float elapsedTime) override;

	void PwUp(int pwMode,bool Up);

	//描画処理
	void Render() override;

	//GUI描画
	void DrawGUI() override;
};
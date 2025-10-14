#include "System/Graphics.h"
#include "SceneGame.h"
#include "Player.h"
#include "common.h"
#include "System/Input.h"
#include "SceneManager.h"
#include "SceneResult.h"
#include "foodManager.h"
#include "Floor.h"

#include "SceneTitle.h"

SceneGame::SceneGame()
{
}

// 初期化
void SceneGame::Initialize()
{
	// カーソルを非表示にする
	ShowCursor(FALSE);

	//ステージ初期化
	stageManager = std::make_unique<StageManager>();

	player.reset(new Player);

	//カメラ初期化
	Graphics& graphics = Graphics::Instance();
	camera.reset(new Camera);
	camera->SetLookAt(
		DirectX::XMFLOAT3(0, 10, -10),
		DirectX::XMFLOAT3(0, 0, 0),
		DirectX::XMFLOAT3(0, 1, 0)
	);
	camera->SetPerspectibeFov(
		DirectX::XMConvertToRadians(45),
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);

	//カメラコントローラー初期化
	cameraController = std::make_unique<CameraController>();

	//テスト用
	foodManager.reset(new FoodManager);

	auto chickinrice = std::make_unique<ChickenRice>();
	chickinrice->setPosition({ 0,0,0 });
	chickinrice.get()->SetLv(2);
	foodManager->Register(std::move(chickinrice));

	auto egg = std::make_unique<Egg>();
	egg->setPosition({ -2,0,-2 });
	egg.get()->SetLv(2);
	foodManager->Register(std::move(egg));


	dishManager.reset(new DishManager);

	auto dish = std::make_unique<Dish>();
	dish->setPosition({ -1,0,-1 });
	dishManager->Register(std::move(dish));
}

// 終了化
void SceneGame::Finalize()
{
	player->Finalize();
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{

	GamePad& gamePad = Input::Instance().GetGamePad();

	ShowCursor(TRUE); // カーソルを隠す

	gameLimit -= 1 * elapsedTime;
	if (gameLimit < 0)
	{
		SceneManager::Instance().ChangeScene(new SceneTitle());
		return;
	}

	//カメラコントローラー更新処理
	//DirectX::XMFLOAT3 target = player->GetPosition();
	//カメラ向き設定(変更の余地あり)
	DirectX::XMFLOAT3 target = { 15,0,10 };
	cameraController->SetTarget(target);

	POINT center;
	center.x = SCREEN_W * 0.5f;
	center.y = SCREEN_H * 0.5f;

	//現在のカーソル位置を取得
	//POINT cursor;
	//GetCursorPos(&cursor);

	////クライアント座標に変換
	//ScreenToClient(Graphics::Instance().GetWindowHandle(), &cursor);

	//float ax = (float)(cursor.x - center.x);
	//float ay = (float)(cursor.y - center.y);

	cameraController->Updeate(elapsedTime, camera.get());

	//// カーソルを中央に戻す
	//POINT screenCenter{ (LONG)(SCREEN_W / 2), (LONG)(SCREEN_H / 2) };
	//ClientToScreen(Graphics::Instance().GetWindowHandle(), &screenCenter);
	//SetCursorPos(screenCenter.x, screenCenter.y);

	if (build)
	{
		//ステージ更新処理
		stageManager->Update(elapsedTime,dishManager.get());
	}
	else
	{
		foodManager->Update(elapsedTime);

		dishManager->Update(elapsedTime);
		//プレイヤー更新処理
		player->Update(elapsedTime, camera.get(), stageManager.get(), foodManager.get(),dishManager.get());
	}
}

// 描画処理
void SceneGame::Render()
{
	if (gameLimit < 0)
	{
		return;
	}

	Graphics& graphics           = Graphics::Instance();
	ID3D11DeviceContext* dc      = graphics.GetDeviceContext();
	ShapeRenderer* shapeRenderer = graphics.GetShapeRenderer();
	ModelRenderer* modelRenderer = graphics.GetModelRenderer();

	// 描画準備
	RenderContext rc;
	rc.deviceContext  = dc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f };	// ライト方向（下方向）
	rc.renderState    = graphics.GetRenderState();

	//カメラパラメータ設定
	rc.view           = camera->GetView();
	rc.projection     = camera->GetProjection();

	{
		//// ビュー行列
		//{
		//	DirectX::XMFLOAT3 eye = { 0, 10, -10 };	// カメラの視点（位置）
		//	DirectX::XMFLOAT3 focus = { 0, 0, 0 };	// カメラの注視点（ターゲット）
		//	DirectX::XMFLOAT3 up = { 0, 1, 0 };		// カメラの上方向

		//	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
		//	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
		//	DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);
		//	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
		//	DirectX::XMStoreFloat4x4(&rc.view, View);
		//}

		//// プロジェクション行列
		//{
		//	float fovY = DirectX::XMConvertToRadians(45);	// 視野角
		//	float aspectRatio = graphics.GetScreenWidth() / graphics.GetScreenHeight();	// 画面縦横比率
		//	float nearZ = 0.1f;	// カメラが映し出すの最近距離
		//	float farZ = 1000.0f;	// カメラが映し出すの最遠距離
		//	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY, aspectRatio, nearZ, farZ);
		//	DirectX::XMStoreFloat4x4(&rc.projection, Projection);
		//}
	}

	// 3Dモデル描画
	{
		//ステージ描画
		stageManager->Render(rc, modelRenderer);

		if (build == false)
		{
			//プレイヤー描画
			player->Render(rc, modelRenderer);

			//ご飯描画
			foodManager->Render(rc, modelRenderer);

			//皿描画
			dishManager->Render(rc, modelRenderer);
		}
	}

	// 3Dデバッグ描画
	{

		stageManager->RenderDebugPrimitive(rc, shapeRenderer);
		if (build == false)
		{
			//プレイヤーデバッグプリミティブ描画
			player->RenderDebugPrimitive(rc, shapeRenderer);
		}
	}

	// 2Dスプライト描画
	{
	}
}

// GUI描画
void SceneGame::DrawGUI()
{
	//プレイヤーデバッグ描画
	//player->DrawDebugGUI();
	player->DrawDebugGUI();
}

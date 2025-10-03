#include "SceneLoading.h"
#include "System/Graphics.h"
#include "System/Input.h"
#include "SceneManager.h"

//ローディングスレッド
void SceneLoading::LoadingThread(SceneLoading* scene)
{
	//COM関連の初期化でスレッドマイに呼ぶ必要がある
	CoInitialize(nullptr);

	//次のシーンの初期化を行う
	scene->nextScene->Initialize();

	//スレッドが終わる前にCOM関連書終了化
	CoUninitialize();

	//次のシーンの準備完了設定
	scene->nextScene->SetReady();
}

void SceneLoading::Initialize()
{
	//スプライト初期化
	sprite = new Sprite("Data/Sprite/LoadingIcon.png");

	//スレッド開始
	thread = new std::thread(LoadingThread,this);
}

void SceneLoading::Finalize()
{
	//スレッド終了化
	if (thread != nullptr)
	{
		delete thread;
		thread = nullptr;
	}

	//スプライト終了化
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void SceneLoading::Update(float elapsedTime)
{
	constexpr float speed = 180;
	angle += speed * elapsedTime;

	//次のシーンの準備が完了したらシーン切り替え
	thread->join();
	if (nextScene->IsReady())
	{
		SceneManager::Instance().ChangeScene(nextScene);
	}
}

void SceneLoading::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	RenderState* renderState = graphics.GetRenderState();

	//描画準備
	RenderContext rc;
	rc.deviceContext = dc;
	rc.renderState = graphics.GetRenderState();

	//2Dスプライト描画
	{
		//画面右下にローディング描画
		float screenWidth = static_cast<float>(graphics.GetScreenWidth());
		float screenHeight = static_cast<float>(graphics.GetScreenHeight());
		float spriteWidth = 256;
		float spriteHeight = 256;
		float positionX = screenWidth - spriteWidth;
		float positionY = screenHeight - spriteHeight;

		sprite->Render(rc,
			positionX, positionY, 0, spriteWidth, spriteHeight,
			angle,
			1, 1, 1, 1);
	}
}

void SceneLoading::DrawGUI()
{
}

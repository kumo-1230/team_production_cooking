#include "System/Graphics.h"
#include "SceneGame.h"
#include "EnemyManager.h"
#include "EnemySlime.h"
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

// ������
void SceneGame::Initialize()
{
	// �J�[�\�����\���ɂ���
	ShowCursor(FALSE);

	//�X�e�[�W������
	stageManager = std::make_unique<StageManager>();

	player.reset(new Player);

	//�J����������
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

	//�J�����R���g���[���[������
	cameraController = std::make_unique<CameraController>();

	//�G�l�~�[����
	enemyManager.reset(new EnemyManager);
	EnemySlime* enemy;
	//for (int i = 0; i < 2; i++)
	{
		enemy = new EnemySlime();
		enemy->SetPosition({ 5.0f,0,5.0f });
		enemyManager->Register(enemy);
	}

	//�e�X�g�p
	foodManager.reset(new FoodManager);
	Rice* rice;
	{
		rice = new Rice();
		rice->setPosition({ 0.0f,0.0f,0.0f });
		foodManager->Register(rice);
	}

}

// �I����
void SceneGame::Finalize()
{
	player->Finalize();

	//�G�l�~�[�I����
	enemyManager->Clear();
}

// �X�V����
void SceneGame::Update(float elapsedTime)
{

	GamePad& gamePad = Input::Instance().GetGamePad();

	ShowCursor(TRUE); // �J�[�\�����B��

	gameLimit -= 1 * elapsedTime;
	if (gameLimit < 0 || enemyManager->GetEnemyCount() <= 0 || player->GetHP() <= 0.0f)
	{
		SceneManager::Instance().ChangeScene(new SceneTitle());
		return;
	}

	//�J�����R���g���[���[�X�V����
	//DirectX::XMFLOAT3 target = player->GetPosition();
	//�J���������ݒ�(�ύX�̗]�n����)
	DirectX::XMFLOAT3 target = { 15,0,10 };
	cameraController->SetTarget(target);

	POINT center;
	center.x = SCREEN_W * 0.5f;
	center.y = SCREEN_H * 0.5f;

	//���݂̃J�[�\���ʒu���擾
	//POINT cursor;
	//GetCursorPos(&cursor);

	////�N���C�A���g���W�ɕϊ�
	//ScreenToClient(Graphics::Instance().GetWindowHandle(), &cursor);

	//float ax = (float)(cursor.x - center.x);
	//float ay = (float)(cursor.y - center.y);

	cameraController->Updeate(elapsedTime, camera.get());

	//// �J�[�\���𒆉��ɖ߂�
	//POINT screenCenter{ (LONG)(SCREEN_W / 2), (LONG)(SCREEN_H / 2) };
	//ClientToScreen(Graphics::Instance().GetWindowHandle(), &screenCenter);
	//SetCursorPos(screenCenter.x, screenCenter.y);



		//�X�e�[�W�X�V����
		stageManager->Updeate(elapsedTime);


		foodManager->Update(elapsedTime);

		//�v���C���[�X�V����
		//player->Update(elapsedTime);
		player->Update(elapsedTime,camera.get(), enemyManager.get(), stageManager.get(),foodManager.get());


		//�G�l�~�[�X�V����
		enemyManager->Update(elapsedTime, player.get(), stageManager->GetFloor());

		if (build) {}



}

// �`�揈��
void SceneGame::Render()
{
	if (gameLimit < 0 || enemyManager->GetEnemyCount() <= 0 || player->GetHP() <= 0.0f)
	{
		return;
	}

	Graphics& graphics           = Graphics::Instance();
	ID3D11DeviceContext* dc      = graphics.GetDeviceContext();
	ShapeRenderer* shapeRenderer = graphics.GetShapeRenderer();
	ModelRenderer* modelRenderer = graphics.GetModelRenderer();

	// �`�揀��
	RenderContext rc;
	rc.deviceContext  = dc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f };	// ���C�g�����i�������j
	rc.renderState    = graphics.GetRenderState();

	//�J�����p�����[�^�ݒ�
	rc.view           = camera->GetView();
	rc.projection     = camera->GetProjection();

	{
		//// �r���[�s��
		//{
		//	DirectX::XMFLOAT3 eye = { 0, 10, -10 };	// �J�����̎��_�i�ʒu�j
		//	DirectX::XMFLOAT3 focus = { 0, 0, 0 };	// �J�����̒����_�i�^�[�Q�b�g�j
		//	DirectX::XMFLOAT3 up = { 0, 1, 0 };		// �J�����̏����

		//	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
		//	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
		//	DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);
		//	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
		//	DirectX::XMStoreFloat4x4(&rc.view, View);
		//}

		//// �v���W�F�N�V�����s��
		//{
		//	float fovY = DirectX::XMConvertToRadians(45);	// ����p
		//	float aspectRatio = graphics.GetScreenWidth() / graphics.GetScreenHeight();	// ��ʏc���䗦
		//	float nearZ = 0.1f;	// �J�������f���o���̍ŋߋ���
		//	float farZ = 1000.0f;	// �J�������f���o���̍ŉ�����
		//	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY, aspectRatio, nearZ, farZ);
		//	DirectX::XMStoreFloat4x4(&rc.projection, Projection);
		//}
	}

	// 3D���f���`��
	{
		//�X�e�[�W�`��
		stageManager->Render(rc, modelRenderer);

		//�v���C���[�`��
		//player->Render(rc, modelRenderer);
		player->Render(rc, modelRenderer);

		//�G�l�~�[�`��
		enemyManager->Render(rc, modelRenderer);

		//���ѕ`��
		foodManager->Render(rc, modelRenderer);
	}

	// 3D�f�o�b�O�`��
	{
		stageManager->RenderDebugPrimitive(rc, shapeRenderer);

		//�v���C���[�f�o�b�O�v���~�e�B�u�`��
		player->RenderDebugPrimitive(rc, shapeRenderer);
	}

	// 2D�X�v���C�g�`��
	{
	}
}

// GUI�`��
void SceneGame::DrawGUI()
{
	//�v���C���[�f�o�b�O�`��
	//player->DrawDebugGUI();
	player->DrawDebugGUI();
}

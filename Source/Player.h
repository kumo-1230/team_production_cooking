#pragma once

#include "System/ModelRenderer.h"
#include "Character.h"
#include "Effect.h"
#include "System/AudioSource.h"
#include "Camera.h"
#include <memory>
#include "StageManager.h"

//�v���C���[
class Player : public Character
{
private:
	std::unique_ptr<Model> model = nullptr;
	float moveSpeed = 5.0f;

	float turnSpeed = DirectX::XMConvertToRadians(720);

	float jumpSpeed = 12.0f;

	int jumpCount = 0;
	int jumpLimit = 2;

	DirectX::XMFLOAT3 p, l;

	Effect* hitEffect = nullptr;

	AudioSource* hitSE = nullptr;

private:
	//Player();
	//~Player() override;
public:
	Player();
	~Player() override;

	//������
	void Initialize();

	//�I����
	void Finalize();

public:
	//�X�V����
	void Update(float elapsedTime,const Camera* camera, EnemyManager* enemyManager, const StageManager* stage);

	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* render);

	//�f�o�b�O�pGUI�`��
	void DrawDebugGUI();

	//�f�o�b�O�v���~�e�B�u�`��
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	bool ApplyDamage(float dmage, float invincidleTime)override;

protected:
	//���n�����Ƃ��ɌĂ΂��
	void OnLanding() override;

private:
	//�X�e�B�b�N���͒l����ړ��x�N�g�����擾
	DirectX::XMFLOAT3 GetMoveVec(const Camera& camera) const;

private:

	//�ړ����͏���
	void InputMove(float elapsedTime, const Camera* camera);
	//�W�����v���͏���
	void InputJump();

	void UpdateHorizontalMove(float elapsedTime, const Stage* stage) override;

	void UpdateVerticalMove(float elapsedTime, const Stage* stage) override;

	//�e�ۓ��͏���
	void InputProjectile(EnemyManager* enemyManager);

	//�v���C���[�ƃG�l�~�[�Ƃ̏Փˏ���
	void CollisionPlayerVsEnemies(EnemyManager* enemyManager);

};
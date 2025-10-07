#pragma once

#include "System//Graphics.h"
#include "System/Model.h"
#include <memory>


class Ingredients
{
protected:
	std::unique_ptr<Model> model;
	DirectX::XMFLOAT3	position = { 0,0,0 };
	DirectX::XMFLOAT3	angle = { 0,0,0 };
	DirectX::XMFLOAT3	scale = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = {
		//�X�P�[��x
		1, 0, 0, 0,
		//�X�P�[��y
		0, 1, 0, 0,
		//��]
		0, 0, 1, 0,
		//�ʒu
		0, 0, 0, 1
	};

	//���a
	float radius = 0.5f;

	//����
	float height = 2.0f;

	bool ChildOn = false;
public:
	Ingredients();
	~Ingredients();

	//������
	void Initialize();

	//�I����
	void Finalize();
private:
	//�g�����X�t�H�[���X�V
	void UpdateTransfom();


public:
	//�X�V����
	void Update(float elapsedTime, const DirectX::XMFLOAT4X4& ParentT);

	//�`�揈��
	void Render(const RenderContext& rc, ModelRenderer* render);

	//�f�o�b�O�pGUI�`��
	void DrawDebugGUI();

	//�f�o�b�O�v���~�e�B�u�`��
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);


};
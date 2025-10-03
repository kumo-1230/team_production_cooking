#pragma once
#include "System/ModelRenderer.h"
#include <memory>
#include <vector>

class Stage
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
	//�^�C�����[�h
	int mode;

public:
	Stage();
	virtual ~Stage();

	//������
	virtual void Initialize() {};

protected:

	void UpdateTransform();

public:

	//�X�V����
	virtual void Updeate(float elapsedTime);

	//�`�揈��
	virtual void Render(const RenderContext& rc, ModelRenderer* renderer);

	virtual void Event() {};

	const DirectX::XMFLOAT4X4& GetTransform() const { return transform; }
	const Model& GetModel()const { return *model.get(); }
};
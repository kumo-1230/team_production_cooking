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

	int nowLV = 0;

	//���a
	float radius = 0.5f;

	//�����ʂ˂�
	float height = 2.0f;

	enum foodType
	{
		RICE = 0,
		CHICKING,
		CARROT,
		ONION,
		EGG,
	};

	int myFoodType;
public:
	Ingredients();
	~Ingredients();

	//������
	void Initialize();

	//�I����
	void Finalize();


	////////////////////////////////
	virtual void setPosition(const DirectX::XMFLOAT3 pos);
	virtual void setScale(const DirectX::XMFLOAT3 scale);
	virtual const DirectX::XMFLOAT3&  getPosition() { return position; }
	const float  getRadius() { return radius; }
	DirectX::XMFLOAT4X4& getTransform()  { return transform; }
	const DirectX::XMFLOAT3&  getScale() { return scale; }
	const DirectX::XMFLOAT3&  getAngle() { return angle; }
	////////////////////////////////

	////////////////////////////////
	int GetLevel() { return nowLV; }
	void SetLevel(int i) { nowLV = i; }

	int GetType() { return myFoodType; }
	void SetType(int i) { myFoodType = i; }
	////////////////////////////////

private:
public:
	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	virtual	void Render(const RenderContext& rc, ModelRenderer* render) = 0;

	//�f�o�b�O�pGUI�`��
	void DrawDebugGUI();

	//�f�o�b�O�v���~�e�B�u�`��
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	//�g�����X�t�H�[���X�V
	void UpdateTransfom();
protected:
	//virtual void Boil(Ingredients ing) {}

	//virtual void Bake(Ingredients ing) {}

 	//virtual void Cut(Ingredients ing) {}

	//virtual void Fry(Ingredients ing) {}

};
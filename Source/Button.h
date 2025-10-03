#pragma once
#include "System/Sprite.h"
#include <memory>
#include <DirectXMath.h>

//�����_�[���[�h
namespace BUTTON_R_MODE
{
	//�ʏ�
	const int NORMAL(0);
	//������
	const int HALF_INVISIBLE(1);
	//����
	const int INVISIBLE(2);
}

class Button
{
private:
	//�{�^���̃X�v���C�g
	std::unique_ptr<Sprite> sprite;
	//�ꏊ
	DirectX::XMFLOAT2 pos;
	//����
	DirectX::XMFLOAT2 length;
	//���C���[
	int layer;
	//�������Ƃ��ɋA���Ă��鐔��
	int mode;
	//����
	bool valid;
	//�����_�[���[�h
	int renderMode = BUTTON_R_MODE::NORMAL;
public:
	Button(const char* fileName, DirectX::XMFLOAT2 p, DirectX::XMFLOAT2 l, int la,int n,bool v);
	~Button() = default;
public:
	/////////////////////////////////////////////////////

	//�b���n�߂�ꏊ
	void SetPos(DirectX::XMFLOAT2 p) { pos = p; }
	//�`�悷��摜�̒���
	void SetLength(DirectX::XMFLOAT2 l) { length = l; }
	//�{�^���̃��C���[
	int GetLayer() { return layer; }
	//�q�b�g�����{�^�����Ԃ����l
	int GetMode() { return mode; }
	//�������邩�ݒ�
	void SetValid(bool i) { valid = i; }
	//���̔��胂�[�h��ݒ�
	bool GetValid() { return valid; }
	//�����_�[���[�h
	void SetRenderMode(int m) { renderMode = m; }

	/////////////////////////////////////////////////////

public:
	void Render(const RenderContext& rc);

	bool HitButton(const DirectX::XMFLOAT2& p,const DirectX::XMFLOAT2& le);
};
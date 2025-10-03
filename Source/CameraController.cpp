#include "System/Input.h"
#include "CameraController.h"
#include <Windows.h>
#include "common.h"
#include "System/Graphics.h"

//�X�V����
void CameraController::Updeate(float elapsedTime, Camera* camera, float ax, float ay)
{
	{
		//POINT center;
		//center.x = SCREEN_W * 0.5f;
		//center.y = SCREEN_H * 0.5f;

		////���݂̃J�[�\���ʒu���擾
		//POINT cursor;
		//GetCursorPos(&cursor);

		////�N���C�A���g���W�ɕϊ�
		//ScreenToClient(Graphics::Instance().GetWindowHandle(), &cursor);

		//GamePad& gamePad = Input::Instance().GetGamePad();
		//float ax = gamePad.GetAxisRX();
		//float ay = gamePad.GetAxisRY();
		//float ax = (float)(cursor.x - center.x);
		//float ay = (float)(cursor.y - center.y);
	}
	
	//�J������]���x
	//float speed = ACCESS_PROPERTY_SET_GUID * elapsedTime;
	float speed = rollSpeed * elapsedTime;

	//�X�e�B�b�N�̓��͒l�ɕ�����x,y������]
	//X���̉�]����
	angle.y += speed * ax;
	//X���̉�]����
	angle.x += speed * ay;

	//X���̃J������]�𐧌�
	if (angle.x > maxAngleX)
	{
		angle.x = maxAngleX;
	}
	if (angle.x < minAngleX)
	{
		angle.x = minAngleX;
	}

	//Y���̉�]�l��-3.14�`3.14�Ɏ��܂�悤��
	if (angle.y < -DirectX::XM_PI)
	{
		angle.y += DirectX::XM_2PI;
	}
	if (angle.y > DirectX::XM_PI)
	{
		angle.y -= DirectX::XM_2PI;
	}

	//�J������]�n����]�s��ɕϊ�
	DirectX::XMMATRIX Transeform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	//��]�s�񂩂�O�����x�N�g�������o��
	DirectX::XMVECTOR Front = Transeform.r[2];
	DirectX::XMFLOAT3 front;
	DirectX::XMStoreFloat3(&front, Front);

	//�����_������x�N�g�������Ɉ�苗�����ꂽ�J�������_�����߂�
	DirectX::XMFLOAT3 eye;
	eye.x = target.x - front.x * range;
	eye.y = target.y - front.y * range;
	eye.z = target.z - front.z * range;

	camera->SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
}
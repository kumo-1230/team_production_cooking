#include "Effect.h"
#include "System/Graphics.h"
#include "EffectManager.h"

//�R���X�g���N�^
Effect::Effect(const char* filename)
{
	//�G�t�F�N�g��ǂݍ��݂���O�Ƀ��b�N����
	//���}���`�X���b�h��Effect���쐬�����DeviceContext�𓯎��A�N�Z�X����
	//�t���[�Y����\��������̂Ŕr�����䂷��
	std::lock_guard<std::mutex> lock(Graphics::Instance().GetMutex());

	//Effekseer�̃��\�[�X��ǂݍ���
	//Effekseer��UTF-16�̃t�@�C���p�X�ȊO�͑Ή����Ă��Ȃ����ߕ����R�[�h�ϊ����K�v
	char16_t utf16Filenaname[256];
	Effekseer::ConvertUtf8ToUtf16(utf16Filenaname, 256, filename);

	//Effekseer�G�t�F�N�g��ǂݍ���
	Effekseer::ManagerRef effekseerManager = EffectManager::Instance().GetEffekseerManager();

	//Effekseer�G�t�F�N�g����݂���
	effekseerEffect = Effekseer::Effect::Create(effekseerManager, (EFK_CHAR*)utf16Filenaname);
}

//�Đ�
Effekseer::Handle Effect::Play(const DirectX::XMFLOAT3& position, float scale)
{
	Effekseer::ManagerRef effekseerManager = EffectManager::Instance().GetEffekseerManager();

	Effekseer::Handle handle = effekseerManager->Play(effekseerEffect, position.x, position.y, position.z);
	effekseerManager->SetScale(handle, scale, scale, scale);
	return handle;
}

//��~
void Effect::Stop(Effekseer::Handle handle)
{
	Effekseer::ManagerRef effekseerManager = EffectManager::Instance().GetEffekseerManager();

	effekseerManager->StopEffect(handle);
}

void Effect::SetPosition(Effekseer::Handle handle, const DirectX::XMFLOAT3& position)
{
	Effekseer::ManagerRef effekseerManager = EffectManager::Instance().GetEffekseerManager();

	effekseerManager->SetLocation(handle, position.x, position.y, position.z);
}

//�X�P�[���ݒ�
void Effect::SetScale(Effekseer::Handle handle, const DirectX::XMFLOAT3& scale)
{
	Effekseer::ManagerRef effekseerManager = EffectManager::Instance().GetEffekseerManager();

	effekseerManager->SetScale(handle, scale.x, scale.y, scale.z);
}

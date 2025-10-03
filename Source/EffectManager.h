#pragma once

#include <DirectXMath.h>
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>

//�G�t�F�N�g�}�l�[�W���[
class EffectManager
{
private:
	Effekseer::ManagerRef effekseerManager;
	EffekseerRenderer::RendererRef effekseerRender;

private:
	EffectManager() {}
	~EffectManager() {}
public:

	//������
	void Initialize();

	//�I����
	void Finalize();

public:
	//�B��C���X�^���X�擾
	static EffectManager& Instance()
	{
		static EffectManager instance;
		return instance;
	}

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render(const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection);

	//Effecksser�}�l�[�W���[�擾
	Effekseer::ManagerRef GetEffekseerManager() { return effekseerManager; }
};
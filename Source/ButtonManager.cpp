#include "ButtonManager.h"
#include "System/Graphics.h"
#include <ranges>

//�{�^���̒ǉ�
void ButtonManager::SetButton(const char* fileName, DirectX::XMFLOAT2 p, DirectX::XMFLOAT2 l, int la, int n,bool v)
{
	auto newButton = std::make_unique<Button>(fileName, p, l, la, n, v);

	if (buttons.size() == 0)
	{
		buttons.emplace_back(std::move(newButton));
		return;
	}
	else
	{
		for (auto it = buttons.begin();it != buttons.end();it++)
		{
			if (la < (*it)->GetLayer())
			{
				buttons.insert(it, std::move(newButton));
				return;
			}
		}
		buttons.emplace_back(std::move(newButton));
		return;
	}
}

void ButtonManager::Render(const RenderContext& rc)
{
	for (auto& b : buttons)
	{
		b->Render(rc);
	}
}

//���ׂẴ{�^���łǂ�ɓ���������
int ButtonManager::HitButton()
{
	//���݂̃J�[�\���ʒu���擾
	POINT cursor;
	GetCursorPos(&cursor);

	//�N���C�A���g���W�ɕϊ�
	ScreenToClient(Graphics::Instance().GetWindowHandle(), &cursor);

	float size = 10.0f; // �Ⴆ��2�s�N�Z���l��
	DirectX::XMFLOAT2 pos = { ((float)cursor.x) - size * 0.5f, ((float)cursor.y) - size * 0.5f };
	DirectX::XMFLOAT2 len = { size, size }; // ���E����

	for (auto& b : std::ranges::reverse_view(buttons))
	{
		if (b->GetValid() == true)
		{
			if (b->HitButton(pos, len))
			{
				return b->GetMode();
			}
		}
	}
	return -1;
}

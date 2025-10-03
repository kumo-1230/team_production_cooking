#include "Menu.h"
#include <DirectXMath.h>
#include <imgui.h>
#include "imgui_impl_win32.h"       // Win32 �p�o�b�N�G���h
#include "imgui_impl_dx11.h"        // DirectX11 �p�o�b�N�G���h
#include "common.h"

Menu::Menu()
{
	buttonManager.reset(new ButtonManager());
	//buttonManager->SetButton("Data/Sprite/test.png", { 10,10 }, { 100,100 }, 0, 0);
	sprBack.reset(new Sprite("Data/Sprite/menuBack.png"));
}

Menu::~Menu()
{
}

//���������{�^���̒l������
void Menu::Updeat(int* hb)
{
	if (keyInput.GetKeyDown(VK_F1))
	{
		if (menuStart)
		{
			menuStart = false;
		}
		else
		{
			menuStart = true;
		}
	}

	if (menuStart)
	{
		if(keyInput.GetKeyDown(VK_LBUTTON))
		{
			*hb = buttonManager->HitButton();
		}
		else
		{
			*hb = -1;
		}
	}
}

void Menu::Render(const RenderContext& rc, int renderMode)
{
	if (menuStart)
	{
		switch (renderMode)
		{
		case MENU::BACK_ON:
			sprBack->Render(rc, 10, 10, 0, SCREEN_W - 20, SCREEN_H - 20, 0, 1, 1, 1, 1);
			break;
		}
		buttonManager->Render(rc);
	}

	{
		////�Ȃ񂩂̃|�W�V����������Ă���
		//ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
		////�\���ꏊ
		//ImGui::SetNextWindowPos(ImVec2(pos.x + 10, pos.y + 10));
		////�傫��
		//ImGui::SetNextWindowSize(ImVec2(SCREEN_W - 20, SCREEN_H - 20));

		//ImGui::SetNextWindowBgAlpha(0.7f);

		//if (ImGui::Begin("Menu", nullptr))
		//{

		//	if (ImGui::Button("Setting",ImVec2(pos.x + 15,pos.y + 15)))
		//	{
		//		menuMode = 0;
		//		ImGui::SetNextWindowFocus();
		//		ImGui::SetNextWindowPos(ImVec2(10, 10));
		//	}

		//	if (ImGui::Button("Setting",ImVec2(pos.x + 15,pos.y + 25)))
		//	{
		//		menuMode = 1;
		//		ImGui::SetNextWindowFocus();
		//		ImGui::SetNextWindowPos(ImVec2(10, 10));
		//	}

		//	switch (menuMode)
		//	{
		//	case 0:
		//		if (ImGui::CollapsingHeader("Setting"))
		//		{
		//			ImGui::InputInt("mode", &menuMode);
		//		}
		//		ImGui::End();
		//		break;
		//	case 1:
		//		if (ImGui::CollapsingHeader("aaa"))
		//		{
		//			ImGui::InputInt("mode", &menuMode);
		//		}
		//		ImGui::End();
		//		break;
		//	}

			////�g�����X�t�H�[��
			//if (ImGui::CollapsingHeader("Menu", ImGuiTreeNodeFlags_DefaultOpen))
			//{
			//	//�ʒu
			//	//ImGui::InputFloat3("Position", &position.x);

			//	////��]
			//	//DirectX::XMFLOAT3 a;

			//	//a.x = DirectX::XMConvertToDegrees(angle.x);
			//	//a.y = DirectX::XMConvertToDegrees(angle.y);
			//	//a.z = DirectX::XMConvertToDegrees(angle.z);
			//	//ImGui::InputFloat3("Angle", &a.x);
			//	//angle.x = DirectX::XMConvertToRadians(a.x);
			//	//angle.y = DirectX::XMConvertToRadians(a.y);
			//	//angle.z = DirectX::XMConvertToRadians(a.z);

			//	//�X�P�[��
			//	ImGui::End();
			//}
		//}
	}
}

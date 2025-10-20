#include "Cursor.h"
#include "System/Audio.h"
Cursor::Cursor(const DirectX::XMFLOAT3& pos)
{
	Initialize();
	position = pos;
	UpdateTransform();
}

Cursor::~Cursor()
{
}

void Cursor::Initialize()
{
	model = std::make_unique<Model>("Data/Model/cursor/cursor.mdl");
	scale = { 0.1f,0.1f,0.1f };
	key = std::make_unique<KeyInput>();
	setUtensis = Audio::Instance().LoadAudioSource("Data/Sound/SetUtensils.wav");
	setUtensis->SetVolume(15);
}

void Cursor::Update(float elapsedTime, int& x, int& y)
{
	time++;
	if (scale.x >= 0.1f || scale.z <= 0.09f)
	{
		scaleC *= -1;
	}
	scale.x += scaleC * elapsedTime;
	scale.z += scaleC * elapsedTime;
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
	{
		if (time % 10 == 0)
		{
			if (GetAsyncKeyState('A') & 0x8000)
			{
				position.x -= 2.0f;
				x -= 1;
				if (x < 1)
				{
					position.x = 2.0f * 18;
					x = 18;
				}
				setUtensis->Play(false);
			}
			if (GetAsyncKeyState('D') & 0x8000)
			{
				position.x += 2.0f;
				x += 1;
				if (x > 18)
				{
					position.x = 1;
					x = 1;
				}
				setUtensis->Play(false);
			}
			if (GetAsyncKeyState('W') & 0x8000)
			{
				position.z += 2.0f;
				y += 1;
				if (y > 8)
				{
					position.z = 1;
					y = 1;
				}
				setUtensis->Play(false);
			}
			if (GetAsyncKeyState('S') & 0x8000)
			{
				position.z -= 2.0f;
				y -= 1;
				if (y < 1)
				{
					position.z = 2.0f * 8;
					y = 8;
				}
				setUtensis->Play(false);
			}
		}
	}
	else
	{
		if (key->GetKeyDown('A'))
		{
			position.x -= 2.0f;
			x -= 1;
			if (x < 0)
			{
				position.x = 2.0f * 19;
				x = 19;
			}
		}
		if (key->GetKeyDown('D'))
		{
			position.x += 2.0f;
			x += 1;
			if (x > 19)
			{
				position.x = 0;
				x = 0;
			}
		}
		if (key->GetKeyDown('W'))
		{
			position.z += 2.0f;
			y += 1;
			if (y > 9)
			{
				position.z = 0;
				y = 0;
			}
		}
		if (key->GetKeyDown('S'))
		{
			position.z -= 2.0f;
			y -= 1;
			if (y < 0)
			{
				position.z = 2.0f * 9;
				y = 9;
			}
		}
	}
	UpdateTransform();
}

void Cursor::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	Stage::Render(rc, renderer);
}

#pragma once
#include "System/Sprite.h"

class scoreRender {
public:
	void ScoreRenderDigit(RenderContext rc, Sprite* sprite,Sprite* minus, int score,float texSizeX, float texSizeY, float worldPosX, float worldPosY)
	{
		if (score == 0)
		{
			sprite->Render(rc,
				worldPosX + 40,
				worldPosY,
				0.0f,
				texSizeX,
				texSizeY,
				0,
				0,
				texSizeX,
				texSizeY,
				0.0f,
				1.0f,
				1.0f,
				1.0f,
				1.0f);
			return;
		}
		int ketasuu = std::log10(std::abs(score)) + 1;

		bool isNegative = (score < 0);
		int absScore = std::abs(score);

		float w = worldPosX;
		if (score < 0)worldPosX = w + 20;
		else worldPosX = w;

		if (isNegative)
		{
			minus->Render(
				rc,
				worldPosX, worldPosY,
				0.0f,
				texSizeX, texSizeY,
				0, 0,
				64,
				64,
				0.0f,
				1.0f, 1.0f, 1.0f, 1.0f);
		}
		for (int i = ketasuu;i > 0;i--)
		{
			sprite->Render(rc,
				worldPosX + i*texSizeX,
				worldPosY,
				0.0f,
				texSizeX,
				texSizeY,
			    texSizeX * (absScore % 10),
				0,
				texSizeX,
				texSizeY,
				0.0f,
				1.0f,
				1.0f,
				1.0f,
				1.0f);
			absScore /= 10;
		}
	}
};

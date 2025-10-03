#include "mathUtils.h"
#include <stdlib.h>
#include <random>

//指定範囲のランダム値を計算する
float MathUtils::RandomRange(float min, float max, int mode)
{
	std::random_device dc;
	std::mt19937 rd(dc());
	std::uniform_int_distribution<int> disti(static_cast<int>(min), static_cast<int>(max));
	std::uniform_real_distribution distf(min, max);

	if (static_cast<int>(RANDOM_MODE::R_INT) == mode)
	{
		return distf(rd);
	}
	else
	{
		return disti(rd);
	}
}

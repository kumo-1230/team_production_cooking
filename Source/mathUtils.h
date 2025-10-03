#pragma once

//ランダムモード
enum class RANDOM_MODE
{
	R_INT = 0, //イント
	R_FLOAT, //フロート
};

//浮動小数算術
class MathUtils
{
public:
	//指定の範囲のランダム値を計算する
	static float RandomRange(float min, float max,int mode);
};
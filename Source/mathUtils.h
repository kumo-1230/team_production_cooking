#pragma once

//�����_�����[�h
enum class RANDOM_MODE
{
	R_INT = 0, //�C���g
	R_FLOAT, //�t���[�g
};

//���������Z�p
class MathUtils
{
public:
	//�w��͈̔͂̃����_���l���v�Z����
	static float RandomRange(float min, float max,int mode);
};
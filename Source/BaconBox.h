#pragma once

#include "stage.h"

class BaconBox : public Stage
{
private:
	
public:
	BaconBox(DirectX::XMFLOAT3 pos);
	~BaconBox() override;

	//������
	void Initialize()override;

public:
	void Updeate(float elapsedTime) override;
};
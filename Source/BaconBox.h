#pragma once

#include "stage.h"
#include "Box.h"

class BaconBox : public  Box
{
private:
	
public:
	BaconBox(DirectX::XMFLOAT3 pos);
	~BaconBox() override;

	//‰Šú‰»
	void Initialize()override;

public:
	void Update(float elapsedTime) override;
};
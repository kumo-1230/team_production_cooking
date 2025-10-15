#pragma once

#include "Box.h"
#include "foodManager.h"

class BaconBox : public  Box
{
private:
	
public:
	BaconBox(DirectX::XMFLOAT3 pos,int m);
	~BaconBox() override;

	//‰Šú‰»
	void Initialize()override;
};
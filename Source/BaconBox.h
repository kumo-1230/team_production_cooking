#pragma once

#include "stage.h"
#include "Box.h"
#include "foodManager.h"

class BaconBox : public  Box
{
private:
	
public:
	BaconBox(DirectX::XMFLOAT3 pos);
	~BaconBox() override;

	//‰Šú‰»
	void Initialize()override;

public:
	void Update(float elapsedTime, FoodManager* FM) override;
};
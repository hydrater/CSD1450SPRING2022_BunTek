#pragma once
#include "Transform.h"
#include "Component.h"
#include "Button.h"
#include "TextRenderer.h"


class UI_Hp : public GameScript
{
public:

	UI_Hp(void);
	~UI_Hp(void);
	void GenerateHp(int sortingLayer, bool isPlayer, bool isEnemy);

private:


};
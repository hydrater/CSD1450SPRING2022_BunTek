#pragma once
#include "Transform.h"
#include "Component.h"
#include "Button.h"
#include "TextRenderer.h"
#include "GameScript.h"
#include "SpriteRenderer.h"

class UI_Hp : public GameScript
{
public:

	UI_Hp(void);
	~UI_Hp(void);
	void GenerateHpBackground(int sortingLayer, bool isPlayer, bool isEnemy);
	void GenerateHpForeground(int sortingLayer, bool isPlayer, bool isEnemy);
	void UpdateHp(void);
	void StartHp(void);
private:


};
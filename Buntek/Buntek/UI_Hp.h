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
	void GenerateHpBackground(bool _isplayer);
	void Start(void) override;
	void Update(void) override;
	GameObject* hpForeground = 0;
	GameObject* hpBackground = 0;
	bool isplayer = false;
	float health = 1000;
	float maxHealth = 1000;
private:


};
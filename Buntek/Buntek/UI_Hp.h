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
	void GenerateHpBackground(void);
	void GenerateHpForeground(void);
	void Start(void) override;
	void Update(void) override;
	GameObject* hpForeground;
	GameObject* hpBackground;
private:


};
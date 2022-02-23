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
	void GenerateHpBar(bool _isplayer = true, float hpAmt = 100, float maxHpAmt = 100, int barCount = 1, float pixelWidth = 500, float pixelHeight = 40, int border = 10);
	void Start(void) override;
	void Update(void) override;
	void SetHp(float hpAmt);
	void Damage(float damageAmt);
	void UpdateHpBar(float floatinghp);

	float lerpSpeed = 4.0f;
	float timer = 0;
	GameObject* hpForeground = 0,* hpBackground = 0, * hpBackground2 = 0,*hpBarCount = 0;
	int borderSize = 10;
	int maxHpBarNum = 2;
	int hpBarNum = maxHpBarNum;
	bool isplayer = false;
	float health = 100;
	float floatinghealth = health;
	float maxHealth = 100;
private:

};
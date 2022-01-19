#include "UI_Hp.h"
#include "Devtools.h"
#include "System.h"
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "SaveManager.h"

float hp = 100;
UI_Hp::UI_Hp(void)
{

}

UI_Hp::~UI_Hp(void)
{

}

void UI_Hp::GenerateHpBackground(void) //empty white bar
{
	hpBackground = devTools.CreateSpriteGameObject("WhiteTexture.png", 600, 100, AE_GFX_BM_NONE, Vector2(300.f, AEGetWindowHeight() / 2.5f), (short)(5 - 2), 1);
}
void UI_Hp::GenerateHpForeground(void) //bar to update
{
	hpForeground = devTools.CreateSpriteGameObject("WhiteTexture.png", 600, 100, AE_GFX_BM_NONE, Vector2(300.f, AEGetWindowHeight() / 2.5f), (short)(5 - 1), 1);
}
void UI_Hp::Start(void)
{
	//hp = SaveManager.profile.hp;
}

void UI_Hp::Update(void)
{
	float beforeDamageHp = hp;
	hp -= 1;
	if (beforeDamageHp > hp)
	{
		float calculation = beforeDamageHp - hp;
		float sizeReduction = calculation * 10;
		hpForeground->GetComponent<SpriteRenderer>()->Size(hpForeground->GetComponent<SpriteRenderer>()->GetHalfWidth() * 2 - sizeReduction, hpForeground->GetComponent<SpriteRenderer>()->GetHalfHeight() * 2);
	}
}
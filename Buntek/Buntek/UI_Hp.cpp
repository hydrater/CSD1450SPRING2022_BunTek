#include "UI_Hp.h"
#include "Devtools.h"
#include "System.h"
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "SaveManager.h"

UI_Hp::UI_Hp(void)
{

}

UI_Hp::~UI_Hp(void)
{

}

void UI_Hp::GenerateHpBackground(bool _isplayer)
{
	//empty white bar
	hpBackground = devTools.CreateSpriteGameObject("WhiteTexture.png", 600, 100, AE_GFX_BM_NONE, this->Owner()->transform->worldposition, (short)(5 - 2), 1);
	//bar to update
	hpForeground = devTools.CreateSpriteGameObject("WhiteTexture.png", 600, 100, AE_GFX_BM_NONE, this->Owner()->transform->worldposition, (short)(5 - 1), 1);
	SpriteRenderer* hpForegroundRenderer = hpForeground->GetComponent<SpriteRenderer>();
	hpForegroundRenderer->SetColor(1, 0, 0);
	isplayer = _isplayer;
}
void UI_Hp::Start(void)
{
	maxHealth = 1000;
	health = maxHealth;
}

void UI_Hp::Update(void)
{
	health -= 1;
	SpriteRenderer* hpBackgroundRenderer = hpBackground->GetComponent<SpriteRenderer>();
	SpriteRenderer* hpForegroundRenderer = hpForeground->GetComponent<SpriteRenderer>();
	health = AEClamp(health, 0, maxHealth);
	hpForegroundRenderer->Size(hpBackgroundRenderer->GetHalfWidth()*2/ maxHealth * health, hpForegroundRenderer->GetHalfHeight() * 2);
	if(isplayer)
		hpForeground->transform->SetPosition(Vector2(hpBackground->transform->worldposition.x - hpBackgroundRenderer->GetHalfWidth() + hpForegroundRenderer->GetHalfWidth(), hpBackground->transform->worldposition.y));
	else
		hpForeground->transform->SetPosition(Vector2(hpBackground->transform->worldposition.x + hpBackgroundRenderer->GetHalfWidth() - hpForegroundRenderer->GetHalfWidth(), hpBackground->transform->worldposition.y));
}
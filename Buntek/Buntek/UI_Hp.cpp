#include "UI_Hp.h"
#include "Devtools.h"
#include "System.h"
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "SaveManager.h"
#include "TextRenderer.h"

UI_Hp::UI_Hp(void)
{
	maxHealth = 1000;
	health = maxHealth;
	hpBarNum = 5;
}

UI_Hp::~UI_Hp(void)
{

}

void UI_Hp::GenerateHpBar(bool _isplayer)
{
	//empty white bar
	hpBackground = devTools.CreateSpriteGameObject("WhiteTexture.png", 600, 100, AE_GFX_BM_NONE, this->Owner()->transform->worldposition, (short)(5 - 2), 1);
	SpriteRenderer* hpBackgroundRenderer = hpBackground->GetComponent<SpriteRenderer>();
	//bar to update
	hpForeground = devTools.CreateSpriteGameObject("WhiteTexture.png", 600, 100, AE_GFX_BM_NONE, this->Owner()->transform->worldposition, (short)(5 - 1), 1);

	hpBarCount = devTools.CreateSpriteGameObject("WhiteTexture.png", 100, 100, AE_GFX_BM_NONE, Vector2(this->Owner()->transform->worldposition.x, + this->Owner()->transform->worldposition.y + hpBackgroundRenderer->GetHalfHeight()*2), (short)(5 - 1), 1);
	TextRenderer* pBarCountTextRenderer = hpBarCount->AddComponent<TextRenderer>();

	pBarCountTextRenderer->SetFont("Gabriola.ttf");
	pBarCountTextRenderer->SetTextColor(0, 0, 0);
	pBarCountTextRenderer->SetText(std::to_string(hpBarNum));
	pBarCountTextRenderer->SetFontScale(1);
	pBarCountTextRenderer->SetLayer(5);
	pBarCountTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	pBarCountTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

	SpriteRenderer* hpForegroundRenderer = hpForeground->GetComponent<SpriteRenderer>();
	hpForegroundRenderer->SetColor(1, 0, 0);
	isplayer = _isplayer;
}
void UI_Hp::Start(void)
{
	
}

void UI_Hp::Update(void)
{
	health -= 10;
	SpriteRenderer* hpBackgroundRenderer = hpBackground->GetComponent<SpriteRenderer>();
	SpriteRenderer* hpForegroundRenderer = hpForeground->GetComponent<SpriteRenderer>();
	health = AEClamp(health, 0, maxHealth);
	if (health == 0) {
		if (hpBarNum > 0) {
			TextRenderer* pBarCountTextRenderer = hpBarCount->GetComponent<TextRenderer>();
			hpBarNum -= 1;
			pBarCountTextRenderer->SetText(std::to_string(hpBarNum));
			health = maxHealth;
		}
	}
	hpForegroundRenderer->Size(hpBackgroundRenderer->GetHalfWidth()*2/ maxHealth * health, hpForegroundRenderer->GetHalfHeight() * 2);
	if(isplayer)
		hpForeground->transform->SetPosition(Vector2(hpBackground->transform->worldposition.x - hpBackgroundRenderer->GetHalfWidth() + hpForegroundRenderer->GetHalfWidth(), hpBackground->transform->worldposition.y));
	else
		hpForeground->transform->SetPosition(Vector2(hpBackground->transform->worldposition.x + hpBackgroundRenderer->GetHalfWidth() - hpForegroundRenderer->GetHalfWidth(), hpBackground->transform->worldposition.y));
}
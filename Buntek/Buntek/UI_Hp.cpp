#include "UI_Hp.h"
#include "Devtools.h"
#include "System.h"
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "SaveManager.h"
#include "TextRenderer.h"

UI_Hp::UI_Hp(void)
{
	maxHealth = 100;
	health = maxHealth;
	floatinghealth = health;
}

UI_Hp::~UI_Hp(void)
{

}

void UI_Hp::GenerateHpBar(bool _isplayer, float hpAmt, float maxHpAmt, int barCount, float pixelWidth , float pixelHeight, int border)
{
	health = hpAmt;
	maxHealth = maxHpAmt;
	maxHpBarNum = barCount;
	borderSize = border;
	//empty white bar
	hpBackground = devTools.CreateSpriteGameObject("WhiteTexture.png", pixelWidth, pixelHeight, AE_GFX_BM_NONE, this->Owner()->transform->worldposition, (short)(5 - 2), 1);
	hpBackground2 = devTools.CreateSpriteGameObject("WhiteTexture.png", pixelWidth - borderSize, pixelHeight - borderSize, AE_GFX_BM_NONE, this->Owner()->transform->worldposition, (short)(5 - 1), 1);
	SpriteRenderer* hpBackgroundRenderer = hpBackground->GetComponent<SpriteRenderer>();
	//bars to update
	hpForeground = devTools.CreateSpriteGameObject("WhiteTexture.png", pixelWidth- borderSize, pixelHeight - borderSize, AE_GFX_BM_NONE, this->Owner()->transform->worldposition, (short)(5 - 0), 1);
	
	hpBarCount = devTools.CreateSpriteGameObject("WhiteTexture.png", 50, 50, AE_GFX_BM_NONE, Vector2(this->Owner()->transform->worldposition.x, + this->Owner()->transform->worldposition.y + hpBackgroundRenderer->GetHalfHeight()*2), (short)(5 - 1), 1);
	
	TextRenderer* pBarCountTextRenderer = hpBarCount->AddComponent<TextRenderer>();
	hpBarNum = barCount;
	pBarCountTextRenderer->SetFont("Gabriola.ttf");
	pBarCountTextRenderer->SetTextColor(0, 0, 0);
	if (hpBarNum > 1) {
		pBarCountTextRenderer->SetText("x" + std::to_string(hpBarNum));
	}
	else {
		pBarCountTextRenderer->SetText(std::to_string(health));
	}
	
	pBarCountTextRenderer->SetFontScale(1);
	pBarCountTextRenderer->SetLayer(5);
	pBarCountTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	pBarCountTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	
	hpBackground2->GetComponent<SpriteRenderer>()->SetColor(0.5f, 0.5f, 0.5f);
	hpForeground->GetComponent<SpriteRenderer>()->SetColor(1, 0, 0);
	isplayer = _isplayer;
	this->Owner()->AddChild(hpBackground);
	this->Owner()->AddChild(hpBackground2);
	this->Owner()->AddChild(hpForeground);
	this->Owner()->AddChild(hpBarCount);
}
void UI_Hp::Start(void)
{
	
}

void UI_Hp::Update(void)
{
	floatinghealth = lerpF(floatinghealth, health, AEClamp(lerpSpeed * DeltaTime,0,1)); // "Floating" hp for the hp lerping
	float remainderHp = fmodf(floatinghealth, maxHealth / maxHpBarNum);
	if (remainderHp <= 0.1f && floatinghealth != 0) {
		remainderHp = (maxHealth / (float)maxHpBarNum);
	}
	//cout << remainderHp << endl;
	UpdateHpBar(remainderHp);
}

void UI_Hp::SetHp(float hpAmt)
{
	if (health == hpAmt) {
		return;
	}
	health = hpAmt;
	health = AEClamp(health, 0, maxHealth);

	SpriteRenderer* hpBackgroundRenderer = hpBackground->GetComponent<SpriteRenderer>();
	SpriteRenderer* hpForegroundRenderer = hpForeground->GetComponent<SpriteRenderer>();
	int foregroundSize = (int)((hpBackgroundRenderer->GetHalfWidth() * 2) - borderSize);
	float newHpBarNum = ceil(health / (maxHealth / maxHpBarNum));

	
	//Set text objects
	hpBarNum = (int)newHpBarNum;
	if (hpBarNum > 1) {// Multiple bars left
		hpBarCount->GetComponent<TextRenderer>()->SetText("x" + std::to_string(hpBarNum));
	}
	else { // Final Bar of help
		hpBarCount->GetComponent<TextRenderer>()->SetText(std::to_string(health));
	}
}

void UI_Hp::UpdateHpBar(float remainderHp) { // remainder hp is the amount of remaining hp in the current bar;
	SpriteRenderer* hpForegroundRenderer = hpForeground->GetComponent<SpriteRenderer>();
	int foregroundSize = (int)((hpBackground->GetComponent<SpriteRenderer>()->GetHalfWidth() * 2) - borderSize);
	hpForegroundRenderer->Size(foregroundSize * (remainderHp / (maxHealth / maxHpBarNum)), hpForegroundRenderer->GetHalfHeight() * 2);

	if (hpBarNum < 2) {
		hpBarCount->GetComponent<TextRenderer>()->SetText(std::to_string((int)health));
	}
}

void UI_Hp::Damage(float damageAmt)
{
	SetHp(health - damageAmt);
}
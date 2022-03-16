/*!*****************************************************************************
\file Slider.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Slider
*******************************************************************************/

#include "Slider.h"
#include "GameManager.h"

Slider::Slider(void)
{
}

Slider::~Slider(void)
{
}

void Slider::Start(void)
{

}

void Slider::Update(void)
{
	if (GameManager.disableInteraction)
		return;

	if (CheckSliderTriggered(GameManager.GetCursorPosition())) {
		sliderCircle->transform->worldposition.x = currentAmount / maxAmount * xRange + xMin;
		
		sliderBar->GetComponent<SpriteRenderer>()->Size((sliderBackground->GetComponent<SpriteRenderer>()->GetHalfWidth() * 2 - borderSize) * (currentAmount / maxAmount)
			, sliderBar->GetComponent<SpriteRenderer>()->GetHalfHeight()*2);
		sliderBar->transform->worldposition.x = currentAmount / maxAmount * xRange + xMin - sliderBar->GetComponent<SpriteRenderer>()->GetHalfWidth();
	}

}
void Slider::GenerateSlider(float maxAmt, float pixelWidth, float pixelHeight, int border) {
	borderSize = border;
	maxAmount = maxAmt;
	currentAmount = maxAmount / 2;

	sliderBackground = devTools.CreateSpriteGameObject("WhiteTexture.png", pixelWidth, pixelHeight, AE_GFX_BM_NONE, this->Owner()->transform->worldposition, (short)(5 - 2), 1);
	sr = sliderBackground->GetComponent<SpriteRenderer>();

	sliderBar = devTools.CreateSpriteGameObject("WhiteTexture.png", pixelWidth - borderSize, pixelHeight - borderSize, AE_GFX_BM_NONE, this->Owner()->transform->worldposition, (short)(5 - 1), 1);
	sliderBar->GetComponent<SpriteRenderer>()->SetColor(0, 0, 1);

	sliderCircle = devTools.CreateSpriteGameObject("WhiteTexture.png", pixelWidth - borderSize, pixelHeight - borderSize, AE_GFX_BM_NONE, this->Owner()->transform->worldposition, (short)(5 - 0), 1);
	sliderCircle->GetComponent<SpriteRenderer>()->SetColor(0, 1, 1);
}
bool Slider::CheckSliderTriggered(Vector2 mousePos) {
	xMin = sliderBackground->transform->worldposition.x - sr->GetHalfWidth() + borderSize / 2.0f;
	xMax = sliderBackground->transform->worldposition.x + sr->GetHalfWidth() - borderSize / 2.0f;

	if (xMin < mousePos.x && xMax > mousePos.x) {

		if (sliderBackground->transform->worldposition.y - sr->GetHalfHeight() + borderSize / 2.0f < mousePos.y && sliderBackground->transform->worldposition.y + sr->GetHalfHeight() - borderSize / 2.0f > mousePos.y) {
			xRange = xMax - xMin;
			currentAmount = (mousePos.x - xMin) / xRange * maxAmount;
			AEClamp(currentAmount, 0, maxAmount);
			return true;
		}
	}
	return false;
	//add check for rotated button???
}
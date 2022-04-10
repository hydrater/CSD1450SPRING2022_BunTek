/*!*****************************************************************************
\file Slider.cpp
\project Beyond Aurorean Skies
\author: Bryan Boh Tai Hong (90%)
\co-authors: Algene Tan Chuan Hong (2.5%), Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Slider
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#include "Slider.h"
#include "GameManager.h"
#include "AudioEngine.h"

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
	if (AEInputCheckReleased(AEVK_LBUTTON)) {
		triggered = false;
	}
	if (CheckSliderTriggered(GameManager.GetCursorPosition())) {
		sliderCircle->transform->worldposition.x = currentAmount / maxAmount * xRange + xMin;
		
		sliderBar->GetComponent<SpriteRenderer>()->Size((sr->GetHalfWidth() * 2 - sr->GetHalfHeight() * 2) * (currentAmount / maxAmount)
			, sliderBar->GetComponent<SpriteRenderer>()->GetHalfHeight()*2);
		sliderBar->transform->worldposition.x = currentAmount / maxAmount * xRange + xMin - sliderBar->GetComponent<SpriteRenderer>()->GetHalfWidth();
	}
}

void Slider::GenerateSlider(float curAmt, short sortingLayer, float maxAmt, float pixelWidth, float pixelHeight, int border) {
	borderSize = border;
	maxAmount = maxAmt;
	currentAmount = curAmt;

	sliderBackground = devTools.CreateSpriteGameObject("WhiteTexture.png", pixelWidth, pixelHeight/2.5f, AE_GFX_BM_NONE, this->Owner()->transform->worldposition, (short)(sortingLayer), 1);
	sr = sliderBackground->GetComponent<SpriteRenderer>();
	this->Owner()->AddChild(sliderBackground);

	xMin = sliderBackground->transform->worldposition.x - sr->GetHalfWidth() + sr->GetHalfHeight();
	xMax = sliderBackground->transform->worldposition.x + sr->GetHalfWidth() - sr->GetHalfHeight();
	xRange = xMax - xMin;

	sliderBar = devTools.CreateSpriteGameObject("WhiteTexture.png", pixelWidth - sr->GetHalfHeight()*2, pixelHeight - borderSize, AE_GFX_BM_NONE, this->Owner()->transform->worldposition, (short)(sortingLayer + 1), 1);
	sliderBar->GetComponent<SpriteRenderer>()->SetColor(0, 0, 1);
	sliderBar->GetComponent<SpriteRenderer>()->Size((sr->GetHalfWidth() * 2 - sr->GetHalfHeight() * 2) * (currentAmount / maxAmount)
		, sliderBar->GetComponent<SpriteRenderer>()->GetHalfHeight() / 2);
	sliderBar->transform->worldposition.x = currentAmount / maxAmount * xRange + xMin - sliderBar->GetComponent<SpriteRenderer>()->GetHalfWidth();
	this->Owner()->AddChild(sliderBar);

	sliderCircle = devTools.CreateSpriteGameObject("hdCircle.png", pixelHeight, pixelHeight, AE_GFX_BM_BLEND, this->Owner()->transform->worldposition, (short)(sortingLayer + 2), 1);
	sliderCircle->transform->worldposition.x = currentAmount / maxAmount * xRange + xMin;
	this->Owner()->AddChild(sliderCircle);
}

bool Slider::CheckSliderTriggered(Vector2 mousePos) {
	if ((xMin <= mousePos.x && xMax >= mousePos.x) && !triggered) {

		if (sliderCircle->transform->worldposition.y - sliderCircle->GetComponent<SpriteRenderer>()->GetHalfHeight() < mousePos.y
			&& sliderCircle->transform->worldposition.y + sliderCircle->GetComponent<SpriteRenderer>()->GetHalfHeight() > mousePos.y) {
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				triggered = true;
			}
		}
	}
	if (triggered) {
		float tempX = mousePos.x;
		tempX = AEClamp(tempX, xMin, xMax);
		currentAmount = (tempX - xMin) / xRange * maxAmount;
		currentAmount = AEClamp(currentAmount, 0, maxAmount);
		if (SliderEffect != NULL) {
			SliderEffect(this);
		}
		return true;
	}
	return false;
}
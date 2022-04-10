/*!*****************************************************************************
\file AlphaChanger.cpp
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief:File is used for changing of alpha
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#include "AlphaChanger.h"
#include "hisMath.h"
using namespace Math;

AlphaChanger::AlphaChanger(void)
{
}

AlphaChanger::~AlphaChanger(void)
{
	
}

void AlphaChanger::Start(void)
{
	_sr = gameObject->GetComponent<SpriteRenderer>();
}

void AlphaChanger::Update(void)
{
	if (!on)
		return;

	internalTimer += (float)AEFrameRateControllerGetFrameTime();
	float diff = (alphaRangeMax - alphaRangeMin);
	float transparency = (sinf(((internalTimer * (2 * PI)) / period)+PI/2+offset)) * diff;
	_sr->SetOpacity(transparency+alphaRangeMin);
}

void AlphaChanger::SetOscillation(float newPeriod, float alphaMax, float alphaMin, float newOffset) {
	period = newPeriod;
	alphaRangeMax = alphaMax;
	alphaRangeMin = alphaMin;
	offset = newOffset;
}


void AlphaChanger::ToggleOscillation(bool isOn)
{
	on = isOn;
}
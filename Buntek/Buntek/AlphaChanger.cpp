/*!*****************************************************************************
\file AlphaChanger.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief:File is used for changing of alpha
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
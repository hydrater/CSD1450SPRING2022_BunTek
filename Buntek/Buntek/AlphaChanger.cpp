#include "AlphaChanger.h"
#include "hisMath.h"
using namespace Math;

AlphaChanger::AlphaChanger(void)
{
	ID = "alpha changer";
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

}
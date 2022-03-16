/*!*****************************************************************************
\file AlphaChanger.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief:File is used for changing of alpha
*******************************************************************************/

#ifndef ALPHACHANGER_H
#define ALPHACHANGER_H

#include "GameScript.h"
#include "SpriteRenderer.h"
#include <AEEngine.h>

class AlphaChanger : public GameScript
{
public:
	AlphaChanger(void);
	~AlphaChanger(void);
	void Start(void) override;
	void Update(void) override;
	void SetOscillation(float newPeriod, float alphaMax, float alphaMin, float newOffset);
	void ToggleOscillation(bool isOn);

private:
	SpriteRenderer* _sr = 0;
	float period = 6.0f;
	float alphaRangeMax = 1;
	float alphaRangeMin = 0.70f;
	float internalTimer = 0;
	float offset = 0;
	bool on = true;
};
#endif
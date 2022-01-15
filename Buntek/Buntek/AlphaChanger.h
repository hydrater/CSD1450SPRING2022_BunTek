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


private:
	SpriteRenderer* _sr = 0;
	float period = 6.0f;
	float alphaRangeMax = 1;
	float alphaRangeMin = 0.70f;
	float internalTimer = 0;
	float offset = 0;

};
#endif
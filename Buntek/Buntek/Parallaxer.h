#pragma once
#include "GameScript.h"
#include "GameManager.h"
#include "Vector2.h"

class Parallaxer : public GameScript
{
public:
	Parallaxer(void);
	~Parallaxer(void);
	void Start(void) override;
	void Update(void) override;

	Vector2 anchorPoint;
	float distance;
	bool inverseMouseX = false;
	bool inverseMouseY = false;

private:
	

};
/*!*****************************************************************************
\file Parallaxer.h
\project Beyond Aurorean Skies
\author: Steven Koe (80%)
\co-authors: Algene Tan Chuan Hong (5%), Isaiah Lim Ji Rong (5%), Bryan Boh Tai Hong (5%), Goh Kiat Beng (5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Parallaxing
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/
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
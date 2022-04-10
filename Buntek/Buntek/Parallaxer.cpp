/*!*****************************************************************************
\file Parallaxer.cpp
\project Beyond Aurorean Skies
\author: Steven Koe (80%)
\co-authors: Algene Tan Chuan Hong (5%), Isaiah Lim Ji Rong (5%), Bryan Boh Tai Hong (5%), Goh Kiat Beng (5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Parallaxing
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/
#include "Parallaxer.h"

Parallaxer::Parallaxer(void)
{
	distance = 0;
}

Parallaxer::~Parallaxer(void)
{

}

void Parallaxer::Start(void)
{
	anchorPoint = this->Owner()->transform->worldposition;
}

void Parallaxer::Update(void)
{
	Vector2 vecDiff = GameManager.GetCursorPosition();
	
	if (distance > 0) {
		vecDiff.Divide(distance);
		if (inverseMouseX) {
			vecDiff.x = -vecDiff.x;
		}
		if (inverseMouseY) {
			vecDiff.y = -vecDiff.y;
		}

		this->Owner()->transform->worldposition = anchorPoint + vecDiff;
	}
	else if (distance == 0){
		if (inverseMouseX) {
			vecDiff.x = -vecDiff.x;
		}
		if (inverseMouseY) {
			vecDiff.y = -vecDiff.y;
		}
		this->Owner()->transform->worldposition = anchorPoint + vecDiff;
	}
	
}
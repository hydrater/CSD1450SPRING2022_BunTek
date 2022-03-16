/*!*****************************************************************************
\file Parallaxer.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Parallaxing
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
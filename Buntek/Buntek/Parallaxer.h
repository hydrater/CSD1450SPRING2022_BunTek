/*!*****************************************************************************
\file Parallaxer.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Parallaxing
*******************************************************************************/#pragma once
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
/*!*****************************************************************************
\file Slider.h
\project Beyond Aurorean Skies
\author: Bryan Boh Tai Hong (90%)
\co-authors: Algene Tan Chuan Hong (2.5%), Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Slider
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#pragma once
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"

class Slider : public GameScript
{
public:
	Slider(void);
	~Slider(void);
	void Start(void) override;
	void Update(void) override;

	void GenerateSlider(float curAmt, short sortingLayer, float maxAmt = 100, float pixelWidth = 500, float pixelHeight = 40, int border = 10);
	bool CheckSliderTriggered(Vector2 mousePos);

	GameObject* sliderCircle = 0, * sliderBar = 0, * sliderBackground = 0;

	void(*SliderEffect)(Slider*) = NULL;

	int borderSize = 10;
	float maxAmount = 100;
	float currentAmount = 100;
	float xMin = 0, xMax = 0, xRange = 0;
	bool triggered = false;
	SpriteRenderer* sr = 0;

private:

};
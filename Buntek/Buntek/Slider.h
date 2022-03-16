/*!*****************************************************************************
\file Slider.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Slider
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

	void GenerateSlider(float maxAmt = 100, float pixelWidth = 500, float pixelHeight = 40, int border = 10);
	bool CheckSliderTriggered(Vector2 mousePos);

	GameObject* sliderCircle = 0, * sliderBar = 0, * sliderBackground = 0;

	int borderSize = 10;
	float maxAmount = 100;
	float currentAmount = 100;
	float xMin = 0, xMax = 0, xRange = 0;
	SpriteRenderer* sr = 0;

private:

};
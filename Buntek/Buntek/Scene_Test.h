/*!*****************************************************************************
\file Scene_Test.h
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Test Screen
*******************************************************************************/
#pragma once
#include "System.h"
#include "SpriteRenderer.h"
#include "Button.h"

class Scene_Test : public Scene
{
private:
	GameObject* splashimage1 = 0;

	GameObject* splashimage2 = 0;

	GameObject* splashimage3 = 0;

	GameObject* splashimage4 = 0;

	GameObject* splashimage5 = 0;

	GameObject* splashimage6 = 0;

	GameObject* spawner = 0;

public:
    void Start(void) override;
    void Update(void) override;
};

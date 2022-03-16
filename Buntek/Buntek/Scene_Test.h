/*!*****************************************************************************
\file Scene_Test.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
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

/*!*****************************************************************************
\file Scene_HowToPlay.h
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene How to play Screen
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/
#include "System.h"

class Scene_HowToPlay : public Scene
{
public:
    void Start(void) override;
   // void EarlyUpdate(void) override;
    void Update(void) override;
  //  void LateUpdate(void) override;
    const Vector2 backmainBtnPos = Vector2(-825, 400);

private:
    ~Scene_HowToPlay(void) override;
    GameObject* playerGuide = 0, * backmainBtn = 0;
};
#pragma once

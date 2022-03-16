/*!*****************************************************************************
\file Scene_HowToPlay.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene How to play Screen
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

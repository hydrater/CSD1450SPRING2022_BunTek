/*!*****************************************************************************
\file Scene_Options.h
\author: Bryan Boh Tai Hong (90%)
\co-authors: Algene Tan Chuan Hong (2.5%), Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Options Screen
*******************************************************************************/
#include "System.h"

class Scene_Options : public Scene
{
public:
    float musicVolume = 0.05f;

    void Start(void) override;
    // void EarlyUpdate(void) override;
    void Update(void) override;
    //  void LateUpdate(void) override;
private:
    ~Scene_Options(void) override;
    GameObject* header = 0, * credits = 0, * bottom = 0;
};
#pragma once

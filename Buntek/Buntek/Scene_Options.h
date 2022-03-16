/*!*****************************************************************************
\file Scene_Options.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
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

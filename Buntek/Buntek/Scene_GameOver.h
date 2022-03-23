#pragma once
/*!*****************************************************************************
\file Scene_GameOver.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Credits Screen
*******************************************************************************/
#include "System.h"

class Scene_GameOver : public Scene
{
public:
    void Start(void) override;
    //void EarlyUpdate(void) override;
    void Update(void) override;
    //void LateUpdate(void) override;
    //GameObject* GetObjRef(short type);
private:
    ~Scene_GameOver(void) override;
    GameObject* header = 0, *gameOverBackground = 0;
    float gameOverTime = 0;
    //TextRenderer* displayTxt = 0;

};

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

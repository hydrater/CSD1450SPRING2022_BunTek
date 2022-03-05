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
    GameObject* splashimage1 = 0;
    GameObject* splashimage2 = 0;
    GameObject* splashimage3 = 0;
    GameObject* splashimage4 = 0;
    GameObject* splashimage5 = 0;
    GameObject* splashimage6 = 0;
    GameObject* spawner = 0;
};
#pragma once

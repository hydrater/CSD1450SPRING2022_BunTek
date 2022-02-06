#pragma once
#include "System.h"

class Scene_Navigation : public Scene
{
public:
    void Start(void) override;
    void EarlyUpdate(void) override;
    void Update(void) override;
    void LateUpdate(void) override;
private:
    ~Scene_Navigation(void) override;
    GameObject* splashimage1 = 0;
    GameObject* splashimage2 = 0;
    GameObject* splashimage3 = 0;
    GameObject* splashimage4 = 0;
    GameObject* splashimage5 = 0;
    GameObject* splashimage6 = 0;
    GameObject* spawner = 0;
};

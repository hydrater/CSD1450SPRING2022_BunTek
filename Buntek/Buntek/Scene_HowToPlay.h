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

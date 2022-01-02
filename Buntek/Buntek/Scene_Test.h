#pragma once
#include "System.h"
#include "SpriteRenderer.h"

class Scene_Test : public Scene
{
private:
	GameObject* splash;
	SpriteRenderer* testRenderer;
	bool playSound = true;

public:
    void Start(void) override;
    void Update(void) override;
};

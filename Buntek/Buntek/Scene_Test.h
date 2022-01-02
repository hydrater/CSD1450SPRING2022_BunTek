#pragma once
#include "System.h"
#include "SpriteRenderer.h"

class Scene_Test : public Scene
{
private:
	GameObject* splashimage1;
	SpriteRenderer* testRenderer1;
	GameObject* splashimage2;
	SpriteRenderer* testRenderer2;
	bool playSound = true;

public:
    void Start(void) override;
    void Update(void) override;
};

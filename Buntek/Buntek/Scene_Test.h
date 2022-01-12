#pragma once
#include "System.h"
#include "SpriteRenderer.h"

class Scene_Test : public Scene
{
private:
	GameObject* splashimage1 = 0;
	SpriteRenderer* testRenderer1 = 0;
	GameObject* splashimage2 = 0;
	SpriteRenderer* testRenderer2 = 0;

public:
    void Start(void) override;
    void Update(void) override;
};

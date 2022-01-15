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

	GameObject* splashimage3 = 0;
	SpriteRenderer* testRenderer3 = 0;

	GameObject* splashimage4 = 0;
	SpriteRenderer* testRenderer4 = 0;

	GameObject* splashimage5 = 0;
	SpriteRenderer* testRenderer5 = 0;

	GameObject* splashimage6 = 0;
	SpriteRenderer* testRenderer6 = 0;

public:
    void Start(void) override;
    void Update(void) override;
};

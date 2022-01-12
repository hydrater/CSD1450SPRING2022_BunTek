#pragma once
#include "System.h"
#include "SpriteRenderer.h"

class Scene_Test : public Scene
{
private:
<<<<<<< Updated upstream
	GameObject* splashimage1 = 0;
	SpriteRenderer* testRenderer1 = 0;
	GameObject* splashimage2 = 0;
	SpriteRenderer* testRenderer2 = 0;
=======
	GameObject* splashimage1;
	SpriteRenderer* testRenderer1;
	GameObject* splashimage2;
	SpriteRenderer* testRenderer2;
	GameObject* splashimage3;
	SpriteRenderer* testRenderer3;
>>>>>>> Stashed changes

public:
    void Start(void) override;
    void Update(void) override;
};

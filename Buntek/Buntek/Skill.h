#pragma once
#include "BallBehavior.h"
#include "GameScript.h"
#include "GameManager.h"
#include "SpriteRenderer.h"


class Skill : public GameScript
{
public:
	Skill(void);
	~Skill(void);
	void Start(void) override;
	void Update(void) override;
private:

	Transform* transform = 0;
};
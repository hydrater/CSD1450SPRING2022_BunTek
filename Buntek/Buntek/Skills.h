#pragma once
#include "BallBehavior.h"
#include "GameScript.h"
#include "GameManager.h"
#include "SpriteRenderer.h"
#include "Skills.h"


class Skills : public GameScript
{
public:
	Skills(void);
	~Skills(void);
	void Start(void) override;
	void Update(void) override;
	void Effects(string effect, string element);

private:
	Transform* transform = 0;
	string Elementtype = "";
	string Effect = "";
	//<data type> Effect = Null // effect for skills on ball
};
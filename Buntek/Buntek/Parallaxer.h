#pragma once
#include "SpriteRenderer.h"
#include "GameScript.h"

class Parallaxer : public SpriteRenderer
{
public:
	Parallaxer(void);
	~Parallaxer(void);
	void Start(void) override;
	void Update(void) override;

private:


};
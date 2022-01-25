#ifndef BATTLEHANDLER_H
#define BATTLEHANDLER_H
#include "GameScript.h"
#include "SpriteRenderer.h"


class BattleHandler : public GameScript
{
public:
	BattleHandler(void);
	~BattleHandler(void);
	void Start(void) override;
	void Update(void) override;

};

#endif
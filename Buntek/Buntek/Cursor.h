#pragma once
#include "GameScript.h"
#include "SpriteRenderer.h"

// Purpose: An Object to follow the player mouse cursor or follow
//			the coordinate assigned to it

class CursorBehaviour : public GameScript
{
public:
	CursorBehaviour(void);
	~CursorBehaviour(void);
	void Start(void) override;
	void Update(void) override;

	void setplayerpossess(bool _playerpossess);
	void setcursorposition(Vector2 position);

	SpriteRenderer* sr = 0;

private:
	bool playerPossess = false;
	Transform* transform = 0;
};
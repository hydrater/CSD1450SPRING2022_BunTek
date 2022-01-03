#include "Cursor.h"
#include "GameManager.h"
#include "SpriteRenderer.h"

CursorBehaviour::CursorBehaviour(void)
{
}

CursorBehaviour::~CursorBehaviour(void)
{
	
}

void CursorBehaviour::Start(void)
{
	transform = this->Owner()->transform;
}

void CursorBehaviour::Update(void)
{
	// Follow the player position
	if (playerPossess)
	{
		transform->SetPosition(GameManager.GetCursorPosition());
	}
	// Follow the enemy position will be called by the AI
}

void CursorBehaviour::setplayerpossess(bool _playerpossess)
{
	playerPossess = _playerpossess;
}

void CursorBehaviour::setcursorposition(Vector2 position)
{
	if (transform == this->Owner()->transform)
		transform->SetPosition(position);
}
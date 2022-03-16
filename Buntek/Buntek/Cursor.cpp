/*!*****************************************************************************
\file Cursor.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles cursor behaviour
*******************************************************************************/

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

	// Create a Glow Effect
	scale = lerpF(scale, targetScale, scaleSpeed);

	if (scale >= targetScale - 0.01f && scale <= targetScale + 0.01f)
	{
		targetScale = (targetScale == maxScale) ? minScale : maxScale;
		scaleSpeed = RandFloatMinMax(0.005f, 0.025f);
	}

	transform->SetScale(Vector2(scale, scale));

	trans = lerpF(trans, targetTrans, transSpeed);

	if (trans >= targetTrans - 0.01f && trans <= targetTrans + 0.01f)
	{
		targetTrans = (targetTrans == maxTrans) ? minTrans : maxTrans;
		transSpeed = RandFloatMinMax(0.005f, 0.025f);
	}
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
/*!*****************************************************************************
\file Cursor.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles cursor behaviour
*******************************************************************************/

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

	float scaleSpeed = 0.025f;
	float minScale = 0.75f;
	float maxScale = 1;
	float scale = 0.1f;
	float targetScale = 1;

	float transSpeed = 0.025f;
	float minTrans = 0.5f;
	float maxTrans = 1;
	float trans = 0.1f;
	float targetTrans = 1;
};
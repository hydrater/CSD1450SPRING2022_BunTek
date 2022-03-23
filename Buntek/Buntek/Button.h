/*!*****************************************************************************
\file Button.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Button behaviour
*******************************************************************************/

#pragma once
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"

class Button : public GameScript
{
public:
	Button(void);
	~Button(void);
	void Start(void) override;
	void Update(void) override;
	void SetClickable(bool _canClick);
	void SetHoverable(bool _canHover);

	bool CheckTriggered(Vector2 mousePos);

	enum ButtonTypes
	{
		None = 0,
        MoveScene = 1
    };
	ButtonTypes ButtonType = ButtonTypes::None;
	//char fontId = -1;
	string ButtonText = "";
	void(*ButtonEffect)(Button*) = NULL;
	void(*HoverEffect)(Button*) = NULL;
	void(*NotHoverEffect)(Button*) = NULL;
	void(*ClickEffect)(Button*) = NULL;

	GameObject* affectedObject = NULL;
	GameObject* affectedHoverObject = NULL;
	GameObject* affectedClickObject = NULL;

	SpriteRenderer* sr = 0;
	TextRenderer* tr = 0;

	bool hoverplay = true;
private:
	Transform* transform = 0;
	bool canHover = true;
	bool canClick = true;
};
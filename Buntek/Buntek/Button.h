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

	bool CheckTriggered(Vector2 mousePos);

	enum ButtonTypes
	{
		None = 0,
        MoveScene = 1
    };
	ButtonTypes ButtonType = None;
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
private:
	Transform* transform = 0;
	bool canClick = true;
};
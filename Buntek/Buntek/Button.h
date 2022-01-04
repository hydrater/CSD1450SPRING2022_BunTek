#pragma once
#include "GameScript.h"
#include "SpriteRenderer.h"


class Button : public GameScript
{
public:
	Button(void);
	~Button(void);
	void Start(void) override;
	void Update(void) override;

	bool CheckTriggered(Vector2 mousePos);

	enum ButtonTypes
	{
		None = 0,
        MoveScene = 1
    };
	ButtonTypes ButtonType = None;
	//char fontId = -1;
	string ButtonText = "";
	void(*ButtonEffect)(void) = NULL;


	SpriteRenderer* sr = 0;

private:
	Transform* transform = 0;
};
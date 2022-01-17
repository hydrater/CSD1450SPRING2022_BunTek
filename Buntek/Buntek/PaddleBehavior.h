#pragma once
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"

class PaddleBehavior : public GameScript
{
public:
	PaddleBehavior();
	~PaddleBehavior();

	Vector2 position = Vector2(0, 0);
	Vector2 velocity = Vector2(0, 0);

	SpriteRenderer* sr = 0;

	void Start(void) override;
	void Update(void) override;

	void movePaddle(Vector2 mousePos, bool isPlayer);

	void setplayerpaddle(bool _playerpaddle);
	void setspeed(float _speed);
	void setMaxspeed(float _Maxspeed);
	void setMinMoveDist(float _MinMoveDist);

private:
	bool playerPaddle = false;
	float speed = 0;
	float Maxspeed = 0;
	float MinMoveDist = 100;
	Transform* transform = 0;
};
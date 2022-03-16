/*!*****************************************************************************
\file PaddleBehaviour.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Paddle Behaviour
*******************************************************************************/
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
	float timeScalar = 1.0f;

private:
	bool playerPaddle = false;
	float speed = 0;
	float MaxSpeed = 0;
	float MinMoveDist = 100;
	Transform* transform = 0;
};
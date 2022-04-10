/*!*****************************************************************************
\file BallBehaviour.cpp
\project Beyond Aurorean Skies
\author: Bryan Boh Tai Hong (80%)
\co-authors: Algene Tan Chuan Hong (3%), Isaiah Lim Ji Rong (10%), Steven Koe (3%), Goh Kiat Beng (3%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief:File is used for changing of ballbehaviour
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#include "BallBehavior.h"
#include "GameManager.h"
#include "SpriteRenderer.h"
#include "System.h"

BallBehavior::BallBehavior(void)
{
}

BallBehavior::~BallBehavior(void)
{
	CollisionManager2D.RemoveFromList(this->Owner()->GetComponent<CircleCollider>());
	battleInput->RemoveFromList(this);
	GameManager.CameraShake(0.1f * ballPhase, ballPhase * .5f, Vector2(0, 0));
	ballParticle->GetComponent<ParticleSystem>()->DeleteParticleSystem();
}

void BallBehavior::Start(void)
{
	transform = this->Owner()->transform;
	this->Owner()->GetComponent<CircleCollider>()->transform = transform;
}

void BallBehavior::Update(void)
{
	if (timeScalar != 0 && !this->Owner()->remove) {
		for (size_t i = 0; i < statusEffect.size(); ++i)
		{
			if (statusEffect[i].statusTimer > 0) {
				statusEffect[i].statusTimer -= DeltaTime;
			}
			else if (statusEffect[i].statusCount == 0) {
				statusEffect.erase(statusEffect.begin() + i);
			}
		}

		ballParticle->transform->SetPosition(transform->worldposition);
		ballParticleSystem->directionalVector2 = -velocity;

		if (speed > targetSpeed) {
			speed = lerpF(speed, targetSpeed, 4.0f * DeltaTime);
			float speedDiff = speed - targetSpeed;
			if (speedDiff < 20) {
				ballParticleSystem->isEmitting = false;
				if (speedDiff < 1) {
					speed = targetSpeed;
				}
			}
			else {
				ballParticleSystem->isEmitting = true;
			}

		}
		else {
			ballParticleSystem->isEmitting = false;
		};
		//Collision check with left/right wall
		bool leftWall = fabs(transform->worldposition.x - GameManager.areaLeftBoundary) <= radius;
		bool rightWall = fabs(transform->worldposition.x - GameManager.areaRightBoundary) <= radius;

		if (leftWall || rightWall) {
			GameManager.PlayRandomBallSound();
			velocity.x = -velocity.x;
			transform->worldposition.x = AEClamp(transform->worldposition.x, GameManager.areaLeftBoundary + radius, GameManager.areaRightBoundary - radius);
			if (playerPossess) {//enemy ball hits wall
				ArtifactDatabase.ApplyArtifactBehavior(GameManager.enemyArtifactList.behaviorList_WallBounce, !playerPossess, this->Owner());
			}
			else {
				ArtifactDatabase.ApplyArtifactBehavior(GameManager.playerArtifactList.behaviorList_WallBounce, !playerPossess, this->Owner());
			}
			GameObject* spawner = new GameObject();
			if (leftWall) {
				spawner->AddComponent<ParticleSystem>()->SetBurstingParticle(Vector2(1, 0), 1, 10, false, 120, 50, 80, 0, 360, 20, 20, "hdCircle.png", Vector2(GameManager.areaLeftBoundary, transform->worldposition.y), 6, (short)AE_GFX_BM_BLEND, true, true, 0.5f, 1.5f);
			}
			else {
				spawner->AddComponent<ParticleSystem>()->SetBurstingParticle(Vector2(-1, 0), 1, 10, false, 120, 50, 80, 0, 360, 20, 20, "hdCircle.png", Vector2(GameManager.areaRightBoundary, transform->worldposition.y), 6, (short)AE_GFX_BM_BLEND, true, true, 0.5f, 1.5f);
			}

			BallHorizontalCheck();
		}
		
		//Collision check with top/bottom wall
		else if (fabs(transform->worldposition.y - GameManager.areaBottomBoundary) <= radius || fabs(transform->worldposition.y - GameManager.areaTopBoundary) <= radius)
		{
			GameManager.PlayRandomBallSound();
			CollisionManager2D.RemoveFromList(this->Owner()->GetComponent<CircleCollider>());

			if (playerPossess) {//enemy ball hits player goal
				ArtifactDatabase.ApplyArtifactBehavior(GameManager.enemyArtifactList.behaviorList_DealDamage, !playerPossess, this->Owner());
				GameManager.DealDamage((float)ballDamage, playerPossess);
				ArtifactDatabase.ApplyArtifactBehavior(GameManager.playerArtifactList.behaviorList_TakeDamage, playerPossess, this->Owner());
				GameManager.HealthCheck(playerPossess);
				GameManager.HealthCheck(!playerPossess);
			}
			else {
				ArtifactDatabase.ApplyArtifactBehavior(GameManager.playerArtifactList.behaviorList_DealDamage, !playerPossess, this->Owner());
				GameManager.DealDamage((float)ballDamage, playerPossess);
				ArtifactDatabase.ApplyArtifactBehavior(GameManager.enemyArtifactList.behaviorList_TakeDamage, playerPossess, this->Owner());
				GameManager.HealthCheck(playerPossess);
				GameManager.HealthCheck(!playerPossess);
			}
			this->Owner()->Delete();
			return;
		}
		// Collision Check with paddle
		Collider2D* othercol = CollisionManager2D.CheckCollision(col); //null error here when ball ball artifact delete ball
		if (othercol != nullptr && othercol->Owner() && othercol->Owner()->GetComponent<PaddleBehavior>())
		{
			PaddleBehavior* tempPaddle = othercol->Owner()->GetComponent<PaddleBehavior>();
			
			savedCol = othercol;
			bool hasBounced = ReflectBall(playerPossess, (othercol->Owner()));
			if (hasBounced) 
			{
				GameObject* spawner = new GameObject();
				if (playerPossess) {
					spawner->AddComponent<ParticleSystem>()->SetBurstingParticle(Vector2(0, -1), 1, 10, false, 120, 50, 80, 0, 360, 20, 20, "hdCircle.png", Vector2(transform->worldposition.x , transform->worldposition.y+radius/2), 6, (short)AE_GFX_BM_BLEND, true, true, 0.5f, 1.5f);
				}
				else
				{
					spawner->AddComponent<ParticleSystem>()->SetBurstingParticle(Vector2(0, 1), 1, 10, false, 120, 50, 80, 0, 360, 20, 20, "hdCircle.png", Vector2(transform->worldposition.x, transform->worldposition.y - radius / 2), 6, (short)AE_GFX_BM_BLEND, true, true, 0.5f, 1.5f);
				}
				if (ballPhase > 0)
					GameManager.PlayRandomBallSound();
			}
		}
		//ball ball artifact collision check 
		if (othercol != nullptr && savedCol != othercol && othercol->Owner() && othercol->Owner()->GetComponent<BallBehavior>())
		{
			savedCol = othercol;
			if (playerPossess) {//enemy ball hits player ball
				ArtifactDatabase.ApplyArtifactBehavior(GameManager.enemyArtifactList.behaviorList_BallOnBallCollision, !playerPossess, this->Owner());
			}
			else {
				ArtifactDatabase.ApplyArtifactBehavior(GameManager.playerArtifactList.behaviorList_BallOnBallCollision, !playerPossess, this->Owner());
			}
		}
		// Update position and rotation
		//check frozen
		bool frozen = false;
		for (size_t i = 0; i < statusEffect.size(); ++i)
		{
			if (statusEffect[i].statusID == 01) {
				if (statusEffect[i].statusTimer > 0) {
					frozen = true;
				}

			}
		}
		if (!frozen) {
			transform->SetPosition(transform->worldposition + velocity * speed * DeltaTime * timeScalar);
			transform->Rotate(rotSpeed* DeltaTime* timeScalar);
		}
	}
	
}

bool BallBehavior::ReflectBall(bool hasPossession, GameObject* paddle)
{
	bool hasbounced = false;
	if (velocity.y < 0) { 
		if (hasPossession && transform->worldposition.y < GameManager.friendlyAreaY) { //player bounce
			velocity = Vector2(0, 1);
			playerPossess = !playerPossess;
			sr->SetColor(0, 0, 1);
			float xdiff = this->Owner()->transform->worldposition.x - paddle->transform->worldposition.x;
			float sign = xdiff > 0 ? 1.0f : -1.0f;
			float multiplier = xdiff / (paddle->GetComponent<BoxCollider>()->width / 2);
			multiplier =  Clamp((float)pow(multiplier, 2) *sign, (float)-1, (float)1);
			velocity.RotateC(multiplier * angRange);

			ballPhase++;
			if (ballPhase > maxBallPhase) {
				ballPhase = maxBallPhase;
			}
			else {
				targetSpeed += ballPhaseSpeedIncrement;
				speed = targetSpeed;
			}

			float addSpd = paddle->GetComponent<PaddleBehavior>()->velocity.y*350 ;

			if (addSpd > 0) {
				speed += paddleBounceMultiplier * addSpd;
			}
			if (ballPhase > 3) {
				//causeHitPause = true;
			}

			ArtifactDatabase.ApplyArtifactBehavior(GameManager.playerArtifactList.behaviorList_PaddleHit, !playerPossess, this->Owner());
			hasbounced = true;
		}
	}
	else {
		if (!hasPossession && transform->worldposition.y > GameManager.hostileAreaY) { //enemy bounce
			velocity = Vector2(0, -1);
			playerPossess = !playerPossess;
			sr->SetColor(1, 0, 0);
			float xdiff = this->Owner()->transform->worldposition.x - paddle->transform->worldposition.x;
			float sign = xdiff > 0 ? 1.0f : -1.0f;
			float multiplier = xdiff / (paddle->GetComponent<BoxCollider>()->width / 2);
			multiplier = Clamp((float)pow(multiplier, 2) * sign, (float)-1, (float)1);
			velocity.RotateAC(multiplier * angRange);

			ballPhase++;
			if (ballPhase > maxBallPhase)
				ballPhase = maxBallPhase;
			else
				speed += ballPhaseSpeedIncrement;

			ArtifactDatabase.ApplyArtifactBehavior(GameManager.enemyArtifactList.behaviorList_PaddleHit, !playerPossess, this->Owner());
			hasbounced = true;
		}
	}
	switch (ballPhase) {
	case -1:
		ballParticleSystem->SetOpacity(0.05f);
		break;
	case 0:
		ballParticleSystem->SetOpacity(0.05f);
		break;
	case 1:
		ballParticleSystem->SetOpacity(0.1f);
		break;
	case 2:
		ballParticleSystem->SetOpacity(0.2f);
		break;
	case 3:
		ballParticleSystem->SetOpacity(0.4f);
		break;
	case 4:
		ballParticleSystem->SetOpacity(0.6f);
		break;
	case 5:
		ballParticleSystem->SetOpacity(0.7f);
		break;
	case 6:
		ballParticleSystem->SetOpacity(0.85f);
		break;
	default:
		ballParticleSystem->SetOpacity(1.0f);
		break;

	}
	return hasbounced;
}

float BallBehavior::GetSpeed(void)
{
	return speed;
}

void BallBehavior::SetSpeed(float _speed)
{
	speed = _speed > maxSpeed? maxSpeed : _speed;
	targetSpeed = _speed > maxSpeed ? maxSpeed : _speed;
}

void BallBehavior::SetTargetSpeed(float _targetSpeed)
{
	targetSpeed = _targetSpeed > maxSpeed ? maxSpeed : _targetSpeed;
}

void BallBehavior::HitBall(Vector2 mousePos, bool isPlayer)
{
	//playerPossess: Player can click the ball
	if (isPlayer != playerPossess)
		return;

	Transform* tempTransform = Owner()->transform;
	if (transform == nullptr)
		return;

	if ((isPlayer && transform->worldposition.y > GameManager.friendlyAreaY) ||
		(!isPlayer && transform->worldposition.y < GameManager.hostileAreaY))
		return;
}

void BallBehavior::BounceBall(bool isPlayer, GameObject* wall, float angle)
{
	if ((!isPlayer && transform->worldposition.y < GameManager.friendlyAreaY) ||
		(isPlayer && transform->worldposition.y > GameManager.hostileAreaY))
	{
		Vector2 wallCoord = wall->transform->worldposition;
		// Create reflection axis
		Vector2 normal = Vector2(wallCoord.y - transform->worldposition.y, 0.f);
		// Rotate (Vector.rotate goes counter clockwise; Angle is based in clockwise)
		normal.RotateAC(angle);
		normal.Normalize();

		// Get new velocity
		Vector2 proj = normal.operator*(normal.Dot(velocity));
		Vector2 newvel = (proj.operator+(proj)).operator-(velocity);
		velocity = newvel.operator*(-1);

		// Force Direction Limit (Ball going opposite direction)
		velocity.y = (isPlayer && velocity.y > 0 || !isPlayer && velocity.y < 0) ? velocity.y * -1 : velocity.y;
			
		BallHorizontalCheck();

		playerPossess = !playerPossess;
		playerPossess ? sr->SetColor(1, 0, 0) : sr->SetColor(0, 0, 1);
	}
}
void BallBehavior::BallHorizontalCheck(void) {
	float ang = Vector2(1, 0).AngleBetween(velocity) / pi * 180.0f;
	if (0 <= ang && ang <= angRange) {
		if (playerPossess) {
			velocity = Vector2(1, 0);
			velocity.RotateC(angRange);
		}
		else{
			velocity = Vector2(1, 0);
			velocity.RotateAC(angRange);
		}
	}
	else if (180 - angRange < ang && ang <= 180) {
		if (playerPossess) {
			velocity = Vector2(-1, 0);
			velocity.RotateAC(angRange);
		}
		else{
			velocity = Vector2(-1, 0);
			velocity.RotateC(angRange);
		}
	}
}
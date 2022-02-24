#include "BallBehavior.h"
#include "GameManager.h"
#include "SpriteRenderer.h"
#include "System.h"
#include "ParticleSystem.h"

BallBehavior::BallBehavior(void)
{
}

BallBehavior::~BallBehavior(void)
{
	CollisionManager2D.RemoveFromList(this->Owner()->GetComponent<CircleCollider>());
	battleInput->RemoveFromList(this);
	GameManager.CameraShake(0.5, 50, Vector2(0, 0));
}

void BallBehavior::Start(void)
{
	transform = this->Owner()->transform;
	this->Owner()->GetComponent<CircleCollider>()->transform = transform;
}

void BallBehavior::Update(void)
{
	//Collision check with left/right wall
	if (fabs(transform->worldposition.x - GameManager.areaLeftBoundary) <= radius || fabs(transform->worldposition.x - GameManager.areaRightBoundary) <= radius) {
		velocity.x = -velocity.x;
		transform->worldposition.x = AEClamp(transform->worldposition.x, GameManager.areaLeftBoundary + radius, GameManager.areaRightBoundary - radius);
		if (playerPossess) {//enemy ball hits wall
			ArtifactDatabase.ApplyArtifactBehavior(GameManager.enemyArtifactList.behaviorList_WallBounce, !playerPossess, this->Owner());
		}
		else {
			ArtifactDatabase.ApplyArtifactBehavior(GameManager.playerArtifactList.behaviorList_WallBounce, !playerPossess, this->Owner());
		}
		
		BallHorizontalCheck();
	}
	//Collision check with top/bottom wall
	else if (fabs(transform->worldposition.y - GameManager.areaBottomBoundary) <= radius || fabs(transform->worldposition.y - GameManager.areaTopBoundary) <= radius)
	{
		CollisionManager2D.RemoveFromList(this->Owner()->GetComponent<CircleCollider>());
		
		if (playerPossess) {//enemy ball hits player goal
			ArtifactDatabase.ApplyArtifactBehavior(GameManager.enemyArtifactList.behaviorList_DealDamage, !playerPossess, this->Owner());
			GameManager.DealDamage((float)ballDamage, playerPossess);
			ArtifactDatabase.ApplyArtifactBehavior(GameManager.playerArtifactList.behaviorList_TakeDamage, playerPossess, this->Owner());
		}
		else {
			ArtifactDatabase.ApplyArtifactBehavior(GameManager.playerArtifactList.behaviorList_DealDamage, !playerPossess, this->Owner());
			GameManager.DealDamage((float)ballDamage, playerPossess);
			ArtifactDatabase.ApplyArtifactBehavior(GameManager.enemyArtifactList.behaviorList_TakeDamage, playerPossess, this->Owner());
		}
		this->Owner()->Delete();
		return;
	}

	// Collision Check with paddle
	Collider2D* othercol = CollisionManager2D.CheckCollision(col);
	if (othercol != nullptr && othercol->Owner() && othercol->Owner()->GetComponent<PaddleBehavior>())
	{
		ReflectBall(playerPossess, (othercol->Owner()));
	}
	//ball ball artifact collision check not working, null error
	//if (othercol != nullptr && othercol->Owner() && othercol->Owner()->GetComponent<BallBehavior>())
	//{
	//	otherCol = othercol;
	//	if (playerPossess) {//enemy ball hits player ball
	//		ArtifactDatabase.ApplyArtifactBehavior(GameManager.enemyArtifactList.behaviorList_BallOnBallCollision, !playerPossess, this->Owner());
	//	}
	//	else {
	//		ArtifactDatabase.ApplyArtifactBehavior(GameManager.playerArtifactList.behaviorList_BallOnBallCollision, !playerPossess, this->Owner());
	//	}
	//}
	// Update position and rotation
	transform->SetPosition(transform->worldposition + velocity * speed * DeltaTime * timeScalar);
	transform->Rotate(rotSpeed * DeltaTime * timeScalar);
}

void BallBehavior::ReflectBall(bool hasPossession, GameObject* paddle)
{
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
			causeHitPause = true;

			ballPhase++;
			if (ballPhase > 8)
				ballPhase = 8;
			else
				speed += ballPhaseSpeedIncrement;

			ArtifactDatabase.ApplyArtifactBehavior(GameManager.playerArtifactList.behaviorList_PaddleHit, !playerPossess, this->Owner());
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
			if (ballPhase > 8)
				ballPhase = 8;
			else
				speed += ballPhaseSpeedIncrement;

			ArtifactDatabase.ApplyArtifactBehavior(GameManager.enemyArtifactList.behaviorList_PaddleHit, !playerPossess, this->Owner());
		}
	}
}

float BallBehavior::GetSpeed(void)
{
	return speed;
}

void BallBehavior::SetSpeed(float _speed)
{
	speed = _speed > maxSpeed? maxSpeed : _speed;
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
	float ang = Vector2(1, 0).AngleBetween(velocity) / 3.1415926535897932384626433832795f * 180.0f;
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
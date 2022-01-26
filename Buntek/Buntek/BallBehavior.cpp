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

	transform->SetPosition(Vector2(transform->worldposition.x + velocity.x * speed * DeltaTime, transform->worldposition.y + velocity.y * speed * DeltaTime));

	if (fabs(transform->worldposition.x - GameManager.areaLeftBoundary) <= radius || fabs(transform->worldposition.x - GameManager.areaRightBoundary) <= radius) {
		velocity.x = -velocity.x;
		transform->worldposition.x = AEClamp(transform->worldposition.x, GameManager.areaLeftBoundary + radius, GameManager.areaRightBoundary - radius);
		BallHorizontalCheck();
	}
	else if (fabs(transform->worldposition.y - GameManager.areaBottomBoundary) <= radius || fabs(transform->worldposition.y - GameManager.areaTopBoundary) <= radius)
	{
		CollisionManager2D.RemoveFromList(this->Owner()->GetComponent<CircleCollider>());
		GameManager.DealDamage(10, !playerPossess);
		this->Owner()->Delete();
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
		Vector2 normal = Vector2(wallCoord.x - transform->worldposition.x, 0.f);
		// Rotate (Vector.rotate goes counter clockwise; Angle is based in clockwise)
		normal.RotateAC(angle);
		normal.Normalize();

		// Get new velocity
		Vector2 proj = normal.operator*(normal.Dot(velocity));
		Vector2 newvel = (proj.operator+(proj)).operator-(velocity);
		velocity = newvel.operator*(-1);

		// Force Direction Limit (Ball going opposite direction)
		velocity.x = (isPlayer && velocity.x > 0 || !isPlayer && velocity.x < 0) ? velocity.x * -1 : velocity.x;
			
		float ang = Vector2(0, 1).AngleBetween(velocity) / 3.1415926535897932384626433832795f * 180.0f;
		if (0 <= ang && ang < angrange) {
			if (velocity.x < 0) {
				velocity = Vector2(0, 1);
				velocity.RotateAC(-angrange);
			}
			else {
				velocity = Vector2(0, 1);
				velocity.RotateAC(angrange);
			}
		}
		else if (180 - angrange < ang && ang <= 180) {
			//cout << ang << endl;
			if (velocity.x < 0) {
				velocity = Vector2(0, -1);
				velocity.RotateAC(angrange);
			}
			else {
				velocity = Vector2(0, -1);
				velocity.RotateAC(-angrange);
			}
		}

		playerPossess = !playerPossess;
		playerPossess ? sr->SetColor(1, 0, 0) : sr->SetColor(0, 0, 1);
	}
}
void BallBehavior::BallHorizontalCheck(void) {
	float ang = Vector2(1, 0).AngleBetween(velocity) / 3.1415926535897932384626433832795f * 180.0f;
	if (0 <= ang && ang <= angrange) {
		if (playerPossess) {
			velocity = Vector2(1, 0);
			velocity.RotateC(angrange);
		}
		else{
			velocity = Vector2(1, 0);
			velocity.RotateAC(angrange);
		}
	}
	else if (180 - angrange < ang && ang <= 180) {
		if (playerPossess) {
			velocity = Vector2(-1, 0);
			velocity.RotateAC(angrange);
		}
		else{
			velocity = Vector2(-1, 0);
			velocity.RotateC(angrange);
		}
	}
}
#include "BallBehavior.h"
#include "GameManager.h"
#include "SpriteRenderer.h"

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
	this->Owner()->GetComponent<CircleCollider>()->UpdateDimension();
	this->Owner()->GetComponent<CircleCollider>()->transform = transform;

	//Create a Trail
	ballTrail->transform->SetPosition(Vector2(transform->worldposition.x, transform->worldposition.y - (ballTrail->transform->worldscale.y * 20 / 2.f)));
}

void BallBehavior::Update(void)
{
	// Element Virtual
	if (elemVirtual && GameManager.friendlyAreaX < transform->worldposition.x && transform->worldposition.x < GameManager.hostileAreaX)
	{
		sr->SetTransparency(1);
	}
	else if (elemVirtual && !elemVirtualTriggered)
	{
		sr->SetTransparency(0.5f);
		elemVirtualTriggered = true;
	}
	// The ball is translucent until it touches the middle of the field

	transform->SetPosition(Vector2(transform->worldposition.x + velocity.x * speed * (float)AEFrameRateControllerGetFrameTime(), transform->worldposition.y + velocity.y * speed * (float)AEFrameRateControllerGetFrameTime()));

	if (fabs(transform->worldposition.x - GameManager.areaLeftBoundary) <= radius || fabs(transform->worldposition.x - GameManager.areaRightBoundary) <= radius) {
		CollisionManager2D.RemoveFromList(this->Owner()->GetComponent<CircleCollider>());
		this->Owner()->Delete();
		ballTrail->Delete();
	}
	else if (fabs(transform->worldposition.y - GameManager.areaBottomBoundary) <= radius || fabs(transform->worldposition.y - GameManager.areaTopBoundary) <= radius) 
	{
		velocity.y = -velocity.y;
		transform->worldposition.y = AEClamp(transform->worldposition.y, GameManager.areaBottomBoundary + 5, GameManager.areaTopBoundary - 5);
	}

	UpdateTrail();
}

void BallBehavior::AssignListPointer(BattleInput* _battleInput)
{
	battleInput = _battleInput;
}

void BallBehavior::UpdateTrail(void)
{
	// Reset Color and Transform
	srBallTrail->SetColor(sr->GetColor('R'), sr->GetColor('G'), sr->GetColor('B'));
	ballTrail->transform->SetScale(Vector2(1.0, speed / initspeed * 2.0f));

	// Correct ang based on velocity
	float ang = Vector2(0, 1).AngleBetween(velocity) / 3.1415926535897932384626433832795f * 180.0f;
	ang = (velocity.x < 0) ? 360 - ang : ang;
	Vector2 trailoffset = Vector2(0, (double)ballTrail->transform->worldscale.y * 20 / 2.0f);
	trailoffset.Rotate(ang);

	// Update position and offset
	ballTrail->transform->worldposition.x = transform->worldposition.x - velocity.x * 2 - trailoffset.x;
	ballTrail->transform->worldposition.y = transform->worldposition.y - velocity.y * 2 - trailoffset.y;
	ballTrail->transform->SetRotation(ang);
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

	if ((isPlayer && transform->worldposition.x > GameManager.friendlyAreaX) ||
		(!isPlayer && transform->worldposition.x < GameManager.hostileAreaX))
		return;

	float xDelta = mousePos.x - tempTransform->worldposition.x, yDelta = mousePos.y - tempTransform->worldposition.y;

	// Update the delta to prevent almost direct vertical velocity (commented out cuz of weird speed)
	//yDelta = AEClamp(yDelta, GameManager.clickAoERadius * -0.9f, GameManager.clickAoERadius * 0.9f);

	if (abs(xDelta) <= GameManager.clickAoERadius && abs(yDelta) <= GameManager.clickAoERadius)
	{
		float mag = Vector2(xDelta, yDelta).Length();

		if (mag <= GameManager.clickAoERadius) {
			velocity = (Vector2(-(mousePos.x - tempTransform->worldposition.x) / mag, -(mousePos.y - tempTransform->worldposition.y) / mag));

			// Change direction if click is in opposite direction
			if (isPlayer && mousePos.x > tempTransform->worldposition.x || !isPlayer && mousePos.x < tempTransform->worldposition.x)
				velocity.x *= -1;

			playerPossess = !playerPossess;
			playerPossess ? sr->SetColor(1, 0, 0) : sr->SetColor(0, 0, 1);

			float ang = Vector2(0, 1).AngleBetween(velocity) / 3.1415926535897932384626433832795f * 180.0f;
			if (0 <= ang && ang < angrange) {
				if (velocity.x < 0) {
					velocity = Vector2(0, 1);
					velocity.Rotate(-angrange);
					//velocity.Rotate(-(angrange - ang));
				}
				else {
					velocity = Vector2(0, 1);
					velocity.Rotate(angrange);
					//velocity.Rotate(angrange - ang);
				}
			}
			else if (180 - angrange < ang && ang <= 180) {
				//cout << ang << endl;
				if (velocity.x < 0) {
					velocity = Vector2(0, -1);
					velocity.Rotate(angrange);
					//velocity.Rotate(ang - (180 - angrange));
				}
				else {
					velocity = Vector2(0, -1);
					velocity.Rotate(-angrange);
					//velocity.Rotate(-(ang - (180 - angrange)));
				}
			}
		}
	}	
}

void BallBehavior::BounceBall(bool isPlayer)
{
	if ((!isPlayer && transform->worldposition.x < GameManager.friendlyAreaX) ||
		(isPlayer && transform->worldposition.x > GameManager.hostileAreaX))
	{
		velocity.x *= -1;
		playerPossess = !playerPossess;
		playerPossess ? sr->SetColor(1, 0, 0) : sr->SetColor(0, 0, 1);
	}
}
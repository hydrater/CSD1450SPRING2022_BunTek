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

	//Create a Trail
	ballTrail->transform->SetPosition(Vector2(transform->worldposition.x, transform->worldposition.y - (ballTrail->transform->worldscale.y * 20 / 2.f)));
}

void BallBehavior::Update(void)
{
	BallVerticalCheck();

	transform->SetPosition(Vector2(transform->worldposition.x + velocity.x * speed * DeltaTime, transform->worldposition.y + velocity.y * speed * DeltaTime));

	if (fabs(transform->worldposition.x - GameManager.areaLeftBoundary) <= radius || fabs(transform->worldposition.x - GameManager.areaRightBoundary) <= radius) {
		CollisionManager2D.RemoveFromList(this->Owner()->GetComponent<CircleCollider>());
		GameManager.DealDamage(10, !playerPossess);
		ballTrail->Delete();
		this->Owner()->Delete();
	}
	else if (fabs(transform->worldposition.y - GameManager.areaBottomBoundary) <= radius || fabs(transform->worldposition.y - GameManager.areaTopBoundary) <= radius) 
	{
		velocity.y = -velocity.y;
		transform->worldposition.y = AEClamp(transform->worldposition.y, GameManager.areaBottomBoundary + 5, GameManager.areaTopBoundary - 5);
	}

	// Check for collision
	if (this->Owner()->GetComponent<CircleCollider>())
	{
		Collider2D* collision = CollisionManager2D.CheckCollision(this->Owner()->GetComponent<CircleCollider>());
		
		// Possible collision effects
		if (collision != nullptr)
		{
			// Collision with Paddle
			if (collision->Owner() && collision->Owner()->GetComponent<PaddleBehavior>())
			{
				BounceBall(!playerPossess, collision->Owner(), collision->Owner()->transform->worldrotation);
				float timeScale = 0.5f;

				//might change as might not work kb eyes tired pepehands
				#define DeltaTime (float)AEFrameRateControllerGetFrameTime() * timeScale;
				ballParticle = new GameObject();
				ballParticle->AddComponent<ParticleSystem>();
				ballParticle->GetComponent<ParticleSystem>()->SetBurstingParticle(this->velocity, 3, 3, false, 45, 2, 5, 5, 10, 5, 5, "WhiteTexture", this->Owner()->transform->worldposition, 2, AE_GFX_BM_NONE);
				
			}
		}
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
	Vector2 trailoffset = Vector2(0.0f, (float)(ballTrail->transform->worldscale.y) * 20 / 2.0f);
	trailoffset.RotateAC(ang);

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
}

void BallBehavior::BounceBall(bool isPlayer, GameObject* wall, float angle)
{
	if ((!isPlayer && transform->worldposition.x < GameManager.friendlyAreaX) ||
		(isPlayer && transform->worldposition.x > GameManager.hostileAreaX))
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
void BallBehavior::BallVerticalCheck(void) {
	float ang = Vector2(0, 1).AngleBetween(velocity) / 3.1415926535897932384626433832795f * 180.0f;
	if (0 <= ang && ang < angrange) {
		if (velocity.x < 0) {
			velocity = Vector2(0, 1);
			velocity.RotateAC(-angrange);
			//velocity.Rotate(-(angrange - ang));
		}
		else {
			velocity = Vector2(0, 1);
			velocity.RotateAC(angrange);
			//velocity.Rotate(angrange - ang);
		}
	}
	else if (180 - angrange < ang && ang <= 180) {
		//cout << ang << endl;
		if (velocity.x < 0) {
			velocity = Vector2(0, -1);
			velocity.RotateAC(angrange);
			//velocity.Rotate(ang - (180 - angrange));
		}
		else {
			velocity = Vector2(0, -1);
			velocity.RotateAC(-angrange);
			//velocity.Rotate(-(ang - (180 - angrange)));
		}
	}
}
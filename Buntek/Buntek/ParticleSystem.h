#pragma once
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "Devtools.h"


class ParticleSystem : public GameScript
{
public:
	ParticleSystem(void);
	~ParticleSystem(void);
	void Start(void) override;
	void Update(void) override;

	// ========    Lists    ========
	vector<GameObject*> particleList;
	vector<float> timerList;
	vector<float> rotationVelList;
	vector<Vector2> velocityList;
	vector<float> lifespanList;

	// ========    Spawner Attributes    ========
	string textureString = "Steven.jpg";
	short blendMode = AE_GFX_BM_BLEND;
	float xSize = 100;
	float ySize = 100;

	// Directional Vector, will be turned into unit vector
	Vector2 directionalVector2 = Vector2(0, 1);
	// Random launch angle spread
	float angleSpread = 360.0f; //In degrees
	// Random launch power range
	float powerRangeMin = 100.0f;
	float powerRangeMax = 300.0f;	

	// Lifespan time Min and Max
	float maxLifespanMin = 2.0f;
	float maxLifespanMax = 3.0f;

	// Rotational Velocity Min and Max
	float randRotRangeMin = -15.0f;
	float randRotRangeMax = 15.0f;
	

	// ========    Particle Spawning Over Time settings     ========
	float spawnRate = 5.0f; //particles per second
	float internalTimer = 0.0f;
	int maxParticles = 100;
	
	// ========    Particle Bursting Over Time settings    ======== 
	bool isBurst = false; //if set to true, particles all spawn at once and burst
	bool hasSpawned = false;
	int numBurst = 100;
	bool isLoop = true;	//if true, keeps bursting over and over again. Else, deletes self after 1 burst

private:
	
	//SpawnParticle
	void SpawnParticle();
	

};
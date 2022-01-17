#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(void)
{
	
}

ParticleSystem::~ParticleSystem(void)
{
	for (int i = particleList.size() - 1; i >= 0; i--) {
		particleList[i]->Delete();
	}
	particleList.clear();
	velocityList.clear();
	timerList.clear();
	rotationVelList.clear();
	lifespanList.clear();
}

void ParticleSystem::Start(void)
{
	
}

void ParticleSystem::Update(void)
{
	float DeltaTime = (float)AEFrameRateControllerGetFrameTime();
	internalTimer += DeltaTime;
	float MaxTime = (float)1 / spawnRate;

	// If supposed to spawn over time
	if (!isBurst) {
		//Spawn a particle
		if (internalTimer >= MaxTime) {
			internalTimer -= MaxTime;
			SpawnParticle();
		}
	}
	else {
		if (!hasSpawned) {//Has not spawned a burst
			hasSpawned = true;
			//Spawn a burst
			for (int i = 0; i < numBurst; i++) {
				SpawnParticle();
			}
		}
		//if supposed to keep looping burst
		if (isLoop) {
			if (internalTimer >= MaxTime) {
				internalTimer -= MaxTime;
				hasSpawned = false; //Burst again next frame
				cout << "BurstAgain!" << endl;
				cout << particleList.size() << endl;
			}
		}
		else {
			if (internalTimer >= maxLifespanMax) { //If all particles are dead
				this->Owner()->Delete();
			}
		}
		
	}
	

	for (int i = particleList.size()-1; i >= 0; i--) {
		//If lived long enough
		if (timerList[i] > lifespanList[i]) {
			//Delete particle
			particleList[i]->Delete();
			velocityList.erase(velocityList.begin() + i);
			timerList.erase(timerList.begin() + i);
			particleList.erase(particleList.begin() + i);
			rotationVelList.erase(rotationVelList.begin() + i);
		}
		else {//Do particle physics
			particleList[i]->transform->worldposition += velocityList[i]*DeltaTime;
			timerList[i] += DeltaTime;
			particleList[i]->transform->Rotate(rotationVelList[i]*DeltaTime);
		}
	}
}

void ParticleSystem::SpawnParticle(void) {

	//Check if exceeds maxParticles?
	if (particleList.size() >= maxParticles) {
		velocityList.erase(velocityList.begin());
		timerList.erase(timerList.begin());
		rotationVelList.erase(rotationVelList.begin());
		particleList[0]->Delete();
		particleList.erase(particleList.begin());
		lifespanList.erase(lifespanList.begin());
	}

	//Creates particle objects and constituent
	GameObject* temp = devTools.createSpriteGameObject(textureString, xSize, ySize, blendMode, this->Owner()->transform->worldposition);
	particleList.push_back(temp);
	directionalVector2.Normalize();
	Vector2 newVec = directionalVector2;
	newVec.Rotate(RandFloatMinMax(-angleSpread / 2, angleSpread / 2));
	newVec = newVec * RandFloatMinMax(powerRangeMin, powerRangeMax);

	velocityList.push_back(newVec);
	timerList.push_back(0.0f);
	rotationVelList.push_back(RandFloatMinMax(randRotRangeMin,randRotRangeMax));
	lifespanList.push_back(RandFloatMinMax(maxLifespanMin, maxLifespanMax));
}
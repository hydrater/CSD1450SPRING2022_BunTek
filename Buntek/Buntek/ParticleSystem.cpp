#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(void)
{
	
}

ParticleSystem::~ParticleSystem(void)
{
	for (int i = (int)particleList.size() - 1; i >= 0; i--) {
		particleList[i]->Delete();
	}
	particleList.clear();
	velocityList.clear();
	timerList.clear();
	rotationVelList.clear();
	lifespanList.clear();
	sizeList.clear();
}

void ParticleSystem::Start(void)
{
	
}

void ParticleSystem::Update(void)
{
	if (isEmitting) {
		if (!isDeleting) {
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
					}
				}
				else {
					DeleteParticleSystem();
				}
			}
		}
		else {
			if (internalTimer >= maxLifespanMax) {
				this->Owner()->Delete();
			}
		}
		internalTimer += DeltaTime;
	}

	// Particle management, physics+deletion
	for (int i = (int)particleList.size() - 1; i >= 0; i--) {
		//If lived long enough
		if (timerList[i] > lifespanList[i]) {
			//Delete particle
			particleList[i]->Delete();
			velocityList.erase(velocityList.begin() + i);
			timerList.erase(timerList.begin() + i);
			lifespanList.erase(lifespanList.begin()+i);
			particleList.erase(particleList.begin() + i);
			rotationVelList.erase(rotationVelList.begin() + i);
			sizeList.erase(sizeList.begin() + i);
		}
		else {//Do particle physics, shrink, and fade
			particleList[i]->transform->worldposition += velocityList[i] * DeltaTime;
			timerList[i] += DeltaTime;
			particleList[i]->transform->Rotate(rotationVelList[i] * DeltaTime);
			if (isShrink||isFade) {
				SpriteRenderer* temp = particleList[i]->GetComponent<SpriteRenderer>();
				float Ratio = 1-(timerList[i] / lifespanList[i]);

				if (isShrink) temp->Size(Ratio * sizeList[i].x, Ratio * sizeList[i].y);
				if (isFade) temp->SetOpacity(opacity*Ratio);
			}
		}
	}
	
	
}

void ParticleSystem::SetColor(float r, float g, float b) {
	ColorR = r;
	ColorG = g;
	ColorB = b;
}
void ParticleSystem::SetOpacity(float newOpacity) {
	opacity = newOpacity;
}

void ParticleSystem::SpawnParticle(void) {

	//Check if exceeds maxParticles?
	if (particleList.size() >= maxParticles) {
		velocityList.erase(velocityList.begin());
		timerList.erase(timerList.begin());
		rotationVelList.erase(rotationVelList.begin());
		particleList.erase(particleList.begin());
		lifespanList.erase(lifespanList.begin());
		sizeList.erase(sizeList.begin());
		particleList[0]->Delete();
	}

	//Creates particle objects and constituent
	GameObject* temp = devTools.CreateSpriteGameObject(textureString, xSize, ySize, blendMode, this->Owner()->transform->worldposition,renderLayer);
	temp->GetComponent<SpriteRenderer>()->SetColor(ColorR, ColorG, ColorB);
	temp->GetComponent<SpriteRenderer>()->SetOpacity(opacity);
	particleList.push_back(temp);
	directionalVector2.Normalize();
	Vector2 newVec = directionalVector2;
	newVec.RotateAC(RandFloatMinMax(-angleSpread / 2, angleSpread / 2));
	newVec = newVec * RandFloatMinMax(powerRangeMin, powerRangeMax);

	velocityList.push_back(newVec);
	timerList.push_back(0.0f);
	rotationVelList.push_back(RandFloatMinMax(randRotRangeMin,randRotRangeMax));
	lifespanList.push_back(RandFloatMinMax(maxLifespanMin, maxLifespanMax));
	sizeList.push_back(Vector2(xSize,ySize));
}

void ParticleSystem::SetScrollingParticle(
	Vector2 directionalVector, float scrollSpeed, 
	float xDimension, float yDimension, 
	string newTextureString, Vector2 newWorldPos, 
	short newRenderLayer, short newBlendMode,
	bool fade, bool shrink) {
	
	directionalVector2 = directionalVector;
	powerRangeMax = scrollSpeed;
	powerRangeMin = scrollSpeed;
	randRotRangeMin = 0;
	randRotRangeMax = 0;
	xSize = xDimension;
	ySize = yDimension;
	spawnRate = powerRangeMin / xSize;
	maxLifespanMax = 2.0f / spawnRate;
	maxLifespanMin = 2.0f / spawnRate;
	internalTimer = maxLifespanMin / 2;
	renderLayer = newRenderLayer;
	textureString = newTextureString;
	angleSpread = 0;
	blendMode = newBlendMode;
	isFade = fade;
	isShrink = shrink;
	SpawnParticle();
	this->Owner()->transform->worldposition = newWorldPos;
}

void ParticleSystem::SetEmittingParticle(
	Vector2 directionalVector, float newSpawnRate,
	float newAngleSpread, float powerMin, float powerMax, 
	float randRotMin, float randRotMax,
	float xDimension, float yDimension,
	string newTextureString, Vector2 newWorldPos,
	short newRenderLayer, short newBlendMode,
	bool fade, bool shrink, float newLifespanMin, float newLifespanMax) {

	isBurst = false;
	isLoop = true;
	directionalVector2 = directionalVector;
	spawnRate = newSpawnRate;
	randRotRangeMin = randRotMin;
	randRotRangeMax = randRotMax;
	powerRangeMin = powerMin;
	powerRangeMax = powerMax;
	angleSpread = newAngleSpread;
	xSize = xDimension;
	ySize = yDimension;
	textureString = newTextureString;
	this->Owner()->transform->worldposition = newWorldPos;
	blendMode = newBlendMode;
	renderLayer = newRenderLayer;
	isFade = fade;
	isShrink = shrink;
	maxLifespanMin = newLifespanMin;
	maxLifespanMax = newLifespanMax;
	SpawnParticle();
}

void ParticleSystem::SetBurstingParticle(
	Vector2 directionalVector, float newSpawnRate, int newNumBurst, bool newIsLoop,
	float newAngleSpread, float powerMin, float powerMax,
	float randRotMin, float randRotMax,
	float xDimension, float yDimension,
	string newTextureString, Vector2 newWorldPos,
	short newRenderLayer, short newBlendMode,
	bool fade, bool shrink, float newLifespanMin, float newLifespanMax) {

	isBurst = true;
	isLoop = newIsLoop;
	numBurst = (int)newNumBurst;
	spawnRate = newSpawnRate;

	directionalVector2 = directionalVector;
	randRotRangeMin = randRotMin;
	randRotRangeMax = randRotMax;
	powerRangeMin = powerMin;
	powerRangeMax = powerMax;
	angleSpread = newAngleSpread;
	xSize = xDimension;
	ySize = yDimension;
	textureString = newTextureString;
	this->Owner()->transform->worldposition = newWorldPos;
	blendMode = newBlendMode;
	renderLayer = newRenderLayer;
	isFade = fade;
	isShrink = shrink;
	maxLifespanMin = newLifespanMin;
	maxLifespanMax = newLifespanMax;
	//SpawnParticle();
}

void ParticleSystem::DeleteParticleSystem(void) {
	isDeleting = true;
	internalTimer = 0;
}
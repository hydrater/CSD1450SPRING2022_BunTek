/*!*****************************************************************************
\file ParticleSystem.h
\project Beyond Aurorean Skies
\author: Steven Koe (80%)
\co-authors: Algene Tan Chuan Hong (5%), Isaiah Lim Ji Rong (5%), Bryan Boh Tai Hong (5%), Goh Kiat Beng (5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Particle System
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/
#pragma once
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "Devtools.h"
#include "System.h"

class ParticleSystem : public GameScript
{
public:
	ParticleSystem(void);
	~ParticleSystem(void);
	void Start(void) override;
	void Update(void) override;

	// Directional Vector, will be turned into unit vector
	Vector2 directionalVector2 = Vector2(0, 1);

	//Is Emitting
	bool isEmitting = true;

	//Set color and opacity
	void SetColor(float r, float g, float b);
	void SetOpacity(float newOpacity);

	//SpawnParticle
	void SpawnParticle();
	

	void SetScrollingParticle(
		Vector2 directionalVector, float scrollSpeed,
		float xDimension, float yDimension,
		string newTextureString, Vector2 newWorldPos, short newRenderLayer,
		short newBlendMode, bool fade = false, bool shrink = false);

	void SetEmittingParticle(
		Vector2 directionalVector, float newSpawnRate,
		float newAngleSpread, float powerMin, float powerMax,
		float randRotMin, float randRotMax,
		float xDimension, float yDimension,
		string newTextureString, Vector2 newWorldPos,
		short newRenderLayer, short newBlendMode,
		bool fade = true, bool shrink = false,
		float newLifespanMin = 2.0f, float newLifespanMax = 3.0f);

	void SetBurstingParticle(
		Vector2 directionalVector, float newSpawnRate, int newNumBurst, bool newIsLoop,
		float newAngleSpread, float powerMin, float powerMax,
		float randRotMin, float randRotMax,
		float xDimension, float yDimension,
		string newTextureString, Vector2 newWorldPos,
		short newRenderLayer, short newBlendMode,
		bool fade = true, bool shrink = false,
		float newLifespanMin = 2.0f, float newLifespanMax = 3.0f);

	//Stop particle system
	void DeleteParticleSystem();

private:
	// ========    Lists    ========
	vector<GameObject*> particleList;
	vector<float> timerList;
	vector<float> rotationVelList;
	vector<Vector2> velocityList;
	vector<float> lifespanList;
	vector<Vector2> sizeList;

	// ========    Spawner Attributes    ========
	string textureString = "Steven.jpg";
	short blendMode = AE_GFX_BM_BLEND;
	float xSize = 100;
	float ySize = 100;
	short renderLayer = 0;
	bool isDeleting = false;
	bool isFade = false;
	bool isShrink = false;
	
	float ColorR = 1, ColorG = 1, ColorB = 1;
	float opacity = 1;
	
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
	int maxParticles = 1000;
	
	// ========    Particle Bursting Over Time settings    ======== 
	bool isBurst = false; //if set to true, particles all spawn at once and burst
	bool hasSpawned = false;
	int numBurst = 100;
	bool isLoop = true;	//if true, keeps bursting over and over again. Else, deletes self after 1 burst

};
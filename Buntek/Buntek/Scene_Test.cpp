#include "Scene_Test.h"
#include "AudioEngine.h"
#include "Parallaxer.h"
#include "AlphaChanger.h"
#include "ParticleSystem.h"

void Scene_Test::Start(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	splashimage1 = devTools.createSpriteGameObject("Static Stars 1.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	splashimage1->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, 0);
	splashimage2 = devTools.createSpriteGameObject("Static Stars 2.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	splashimage2->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, PI);
	splashimage3 = devTools.createSpriteGameObject("More Stars 1.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	splashimage3->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, 3*PI/2);
	splashimage4 = devTools.createSpriteGameObject("More Stars 2.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	splashimage4->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, PI/2);
	splashimage5 = devTools.createSpriteGameObject("NebulaBig.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));

	//splashimage6 = devTools.createSpriteGameObject("NebulaCloudBig.png", 3960, 1080, AE_GFX_BM_BLEND, Vector2(0, 0),(short)1);
	//splashimage1->AddComponent<Parallaxer>()->distance = 50;

	spawner = new GameObject();
	spawner->transform->worldposition = Vector2(0, 0);
	ParticleSystem* _spawnerPs = spawner->AddComponent<ParticleSystem>();
	_spawnerPs->directionalVector2 = Vector2(-1, 0);
	_spawnerPs->powerRangeMax = 60;
	_spawnerPs->powerRangeMin = 60;
	_spawnerPs->randRotRangeMin = 0;
	_spawnerPs->randRotRangeMax = 0;
	_spawnerPs->xSize = 3960;
	_spawnerPs->ySize = 1080;
	_spawnerPs->spawnRate = _spawnerPs->powerRangeMin / _spawnerPs->xSize;
	_spawnerPs->maxLifespanMax = 2.0f/_spawnerPs->spawnRate;
	_spawnerPs->maxLifespanMin = 2.0f/_spawnerPs->spawnRate;
	_spawnerPs->internalTimer = _spawnerPs->maxLifespanMin / 2;
	_spawnerPs->renderLayer = 1;
	_spawnerPs->textureString = "NebulaCloudBig.png";
	_spawnerPs->angleSpread = 0;
	_spawnerPs->SpawnParticle();
	spawner->transform->worldposition = Vector2(-3960, 0);
}

void Scene_Test::Update(void)
{
	//Vector2 addPos = Vector2((float)(50.0f * DeltaTime), (float)0);
	//splashimage6->transform->worldposition += addPos;
	
}

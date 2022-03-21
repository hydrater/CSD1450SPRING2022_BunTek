/*!*****************************************************************************
\file Scene_Test.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Test Screen
*******************************************************************************/
#include "Scene_Test.h"
#include "AudioEngine.h"
#include "Parallaxer.h"
#include "AlphaChanger.h"
#include "ParticleSystem.h"
#include "UI_DialogueHandler.h"
#include "ArtifactDatabase.h"

void Scene_Test::Start(void)
{
	//AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	//splashimage1 = devTools.CreateSpriteGameObject("Static Stars 1.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	//splashimage1->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, 0);
	//splashimage2 = devTools.CreateSpriteGameObject("Static Stars 2.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	//splashimage2->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, PI);
	//splashimage3 = devTools.CreateSpriteGameObject("More Stars 1.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	//splashimage3->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, 3*PI/2);
	//splashimage4 = devTools.CreateSpriteGameObject("More Stars 2.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	//splashimage4->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, PI/2);
	//splashimage5 = devTools.CreateSpriteGameObject("NebulaBig.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	//splashimage5->AddComponent<AlphaChanger>()->SetOscillation(6.0f, 1.0f, 0.8f, PI / 2);
	//splashimage6 = devTools.CreateSpriteGameObject("NebulaCloudBig.png", 3960, 1080, AE_GFX_BM_BLEND, Vector2(0, 0),(short)1);
	////splashimage1->AddComponent<Parallaxer>()->distance = 50;

	//spawner = new GameObject();
	//spawner->transform->worldposition = Vector2(0, 0);
	//ParticleSystem* _spawnerPs = spawner->AddComponent<ParticleSystem>();

	//_spawnerPs->SetScrollingParticle(
	//	Vector2(-1, 0), 60.0f,
	//	3960, 1080, "NebulaCloudBig.png",
	//	Vector2(-3960, 0),1,(short)AE_GFX_BM_ADD);

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	/*
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	vector<Artifact> artiList;
	Artifact test, test2, test3;
	test.ID = 630;
	test2.ID = 540;
	test3.ID = 420;
	artiList.push_back(test);
	artiList.push_back(test2);
	artiList.push_back(test3);
	//artiList.push_back(test3);
	UIDialogueManager.CreateRewardSelPreset(artiList, 1, true);
	*/
	//spawner = new GameObject();
	//spawner->AddComponent<ParticleSystem>()->SetEmittingParticle(Vector2(0, 1), 100, 360, 30, 40, -10, 10, 10, 10, "ball.png", Vector2(0, 0), 5, (short)AE_GFX_BM_BLEND,true,true);
	//spawner->AddComponent<ParticleSystem>()->SetBurstingParticle(Vector2(-1, 0), 1, 30, false, 120, 50, 80, 0, 360, 20, 20, "ball.png", Vector2(0, 0), 6, (short)AE_GFX_BM_BLEND, true, true,0.5f,1.5f);

	//GameObject* IMNEW = new GameObject();
	//GameObject* IMCHILD = devTools.CreateSpriteGameObject("WhiteTexture.png", 180, 80, AE_GFX_BM_BLEND, Vector2(0, 0), 3, 1.f);
	//cout << "IMNEW EXIST: " << IMNEW << endl;
	//cout << "IMCHILD EXIST: " << IMCHILD << endl;
	//IMNEW->AddChild(IMCHILD);
	////IMCHILD->Deactivate();
	///*IMNEW = 0;
	//IMCHILD = 0;*/
	//cout << "IMNEW SHOULD BE GONE: " << IMNEW << endl;
	//cout << "IMCHILD SHOULD BE GONE: " << IMCHILD << endl;

	Vector2 pos1 = Vector2(0,0);
	Vector2 pos2 = Vector2(50, 50);
	GameObject* LINE = devTools.CreateLineGameObject(pos1, pos2, 0.4f, 0.4f, 1.f, 5, 2, 1.f);
}

void Scene_Test::Update(void)
{
	/*Vector2 addPos = Vector2((float)(50.0f * DeltaTime), .0f);
	splashimage6->transform->worldposition += addPos;*/
	
}

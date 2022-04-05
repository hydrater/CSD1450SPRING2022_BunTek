/*!*****************************************************************************
\file Scene_Options.cpp
\author: Bryan Boh Tai Hong (90%)
\co-authors: Algene Tan Chuan Hong (2.5%), Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Options Screen
*******************************************************************************/

#include "Scene_Test.h"
#include "AudioEngine.h"
#include "Parallaxer.h"
#include "AlphaChanger.h"
#include "ParticleSystem.h"
#include "UI_DialogueHandler.h"
#include "ArtifactDatabase.h"
#include "Scene_Options.h"
void BtnFunc_increaseMusicVolume(Button* button);
//void BtnFuncHover_increaseMusicVolume(Button* button);
//void BtnFuncUnhover_increaseVolume(Button* button);

//void BtnFunc_decreaseMusicVolume(Button* button);
//void BtnFuncHover_decreaseMusicVolume(Button* button);
//void BtnFuncUnhover_decreaseMusicVolume(Button* button);

//void BtnFunc_increaseBattleVolume(Button* button);
//void BtnFuncHover_increaseBattleVolume(Button* button);
//void BtnFuncUnhover_increaseBattleVolume(Button* button);

//void BtnFunc_decreaseBattleVolume(Button* button);
//void BtnFuncHover_decreaseBattleVolume(Button* button);
//void BtnFuncUnhover_decreaseBattleVolume(Button* button);
void Scene_Options::Start(void)
{

}

void Scene_Options::Update(void)
{

}
Scene_Options::~Scene_Options(void)
{

}

void BtnFunc_increaseMusicVolume(Button* button)
{
	if (button->CheckTriggered(Vector2(300, 300)))
	{
		AudioManager.SetMusicVolume( + 0.05f);
	}
}

#include "MapGenerator.h"
#include "UI_Hp.h"
#include "Devtools.h"
#include "System.h"
#include "GameScript.h"
#include "SpriteRenderer.h"

UI_Hp::UI_Hp(void)
{

}

UI_Hp::~UI_Hp(void)
{

}

void UI_Hp::GenerateHpBackground(int sortingLayer, bool isPlayer, bool isEnemy)
{
	GameObject* hpBackground = devTools.CreateSpriteGameObject("paddle.png", 600, 150, AE_GFX_BM_BLEND, Vector2(100.f, AEGetWindowHeight() / 2.5f), (short)(sortingLayer - 1), 0.5f);
}
void UI_Hp::GenerateHpForeground(int sortingLayer, bool isPlayer, bool isEnemy)
{
	GameObject* hpForeground = devTools.CreateSpriteGameObject("paddle.png", 600, 150, AE_GFX_BM_BLEND, Vector2(50.f, AEGetWindowHeight() / 2.5f), (short)(sortingLayer - 1), 0.5f);
}
void UI_Hp::StartHp(void)
{

}

void UI_Hp::UpdateHp(void)
{

}
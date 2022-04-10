/*!*****************************************************************************
\file Devtools.h
\project Beyond Aurorean Skies
\author: Steven Koe (70%)
\co-authors: Algene Tan Chuan Hong (5%), Isaiah Lim Ji Rong (5%), Bryan Boh Tai Hong (15%), Goh Kiat Beng (5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Dev Tools
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/
#pragma once
#include <vector>
#include "Vector2.h"
#include "Component.h"
#include "ArtifactDatabase.h"
#include <AEEngine.h>
#include "SpriteRenderer.h"
#include "TextRenderer.h"

#define devTools _devTools::Instance()

class _devTools
{
private:
    _devTools();
    ~_devTools();
public:
    
    static _devTools& Instance(void);

    //Basic function
    GameObject* CreateSpriteGameObject(string spriteName, float xSize, float ySize, short blendMode, Vector2 pos);

    //Layer option override
    GameObject* CreateSpriteGameObject(string spriteName, float xSize, float ySize, short blendMode, Vector2 pos, short layer);

    //Opacity option override
    GameObject* CreateSpriteGameObject(string spriteName, float xSize, float ySize, short blendMode, Vector2 pos, short layer, float opacity);

    //Basic function
    TextRenderer* AddTextToSpriteGameObject(GameObject* gameObject, string fontName, string text, TextRenderer::xAlignmentTypes xAlignment, TextRenderer::yAlignmentTypes yAlignment, float fontsize);

    //Layer option override
    TextRenderer* AddTextToSpriteGameObject(GameObject* gameObject, string fontName, string text, TextRenderer::xAlignmentTypes xAlignment, TextRenderer::yAlignmentTypes yAlignment, float fontsize, short layer);

    //Warp around option override
    TextRenderer* AddTextToSpriteGameObject(GameObject* gameObject, string fontName, string text, TextRenderer::xAlignmentTypes xAlignment, TextRenderer::yAlignmentTypes yAlignment, float fontsize, short layer, bool warparound);

    //Artifact UI
    GameObject* CreateArtifactRewardCard(unsigned long ID, Vector2 pos, short layer);

    //Artifact Price Tag
    GameObject* CreatePriceTagGameObject(int price, short blendMode, Vector2 pos, short layer);

    //Line
    GameObject* CreateLineGameObject(Vector2 pos1, Vector2 pos2, float R, float G, float B, float thickness, short layer, float opacity);

    //Create artifact object
    GameObject* CreateArtifactObject(Vector2 pos, unsigned long artifact, int count, float xDir, short layer);
};
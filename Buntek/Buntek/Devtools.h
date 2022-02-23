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

    //warp around option override
    TextRenderer* AddTextToSpriteGameObject(GameObject* gameObject, string fontName, string text, TextRenderer::xAlignmentTypes xAlignment, TextRenderer::yAlignmentTypes yAlignment, float fontsize, short layer, bool warparound);

    //Artifact UI
    GameObject* CreateArtifactUIGameObject(Artifact artifact, float xSize, float ySize, short blendMode, Vector2 pos, short layer);
};
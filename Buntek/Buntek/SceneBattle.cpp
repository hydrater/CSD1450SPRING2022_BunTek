#include "SceneBattle.h"

// ------------------------------------ Battle ------------------------------------

AEGfxVertexList* pMesh1;
AEGfxTexture* pTex1;

void Battle::Awake(void)
{
	

}

void Battle::Start(void)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f,
		30.0f, -30.0f, 0x00FFFF00, 1.0f, 1.0f,
		-30.0f, 30.0f, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		30.0f, -30.0f, 0x00FFFFFF, 1.0f, 1.0f,
		30.0f, 30.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-30.0f, 30.0f, 0x00FFFFFF, 0.0f, 0.0f);

	pMesh1 = AEGfxMeshEnd();
	pTex1 = AEGfxTextureLoad("./Resources/Art/PlanetTexture.png");
	AE_ASSERT_MESG(pTex1, "Failed to create texture1!!");
}

void Battle::Update(void)
{
    //set background color
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

}

void Battle::Render(void)
{
	// Call base function test
	//Battle test;
	//test.Scene::Render();

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	//Set Transparency, Transparency will work only if the Blend mode is not NONE.
	AEGfxSetTransparency(1.0f);
	// Set position for object 3
	AEGfxSetPosition(100.0f, 60.0f);
	// Add Blue tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set texture
	AEGfxTextureSet(pTex1, 0, 0);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);
}

void Battle::Free(void)
{
	AEGfxMeshFree(pMesh1);
	AEGfxTextureUnload(pTex1);
}
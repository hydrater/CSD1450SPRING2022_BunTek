#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
	
}

SpriteRenderer::~SpriteRenderer()
{

}

void SpriteRenderer::Size(float width, float height)
{
	float halfwidth = width / 2, halfheight = height / 2;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-halfwidth, -halfheight, 0x00FF00FF, 0.0f, 1.0f,
		halfwidth, -halfheight, 0x00FFFF00, 1.0f, 1.0f,
		-halfwidth, halfheight, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		halfwidth, -halfheight, 0x00FFFFFF, 1.0f, 1.0f,
		halfwidth, halfheight, 0x00FFFFFF, 1.0f, 0.0f,
		-halfwidth, halfheight, 0x00FFFFFF, 0.0f, 0.0f);

	mesh = AEGfxMeshEnd();
	texture = AEGfxTextureLoad("./Resources/Art/PlanetTexture.png");
	AE_ASSERT_MESG(texture, "Failed to create texture1!!");
}

void SpriteRenderer::Render(void)
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	//Set Transparency, Transparency will work only if the Blend mode is not NONE.
	AEGfxSetTransparency(1.0f);
	// Set position for object 3
	AEGfxSetPosition(0.0f, -60.0f);
	// Add Blue tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set texture
	AEGfxTextureSet(texture, 0, 0);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void SpriteRenderer::Free(void)
{
	//AEGfxMeshFree(mesh);
	//AEGfxTextureUnload(texture);
}


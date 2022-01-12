#include "Renderer.h"
#include "AssetManager.h"

_renderer* _renderer::instance = 0;

_renderer::_renderer()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00FF00FF, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00FFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	mesh = AEGfxMeshEnd();
}

_renderer::~_renderer()
{
	AEGfxMeshFree(mesh);
}

_renderer& _renderer::Instance(void)
{
    if (instance != 0)
        return *instance;
    instance = new _renderer();

    return *instance;
}

void _renderer::Update(void)
{
    for (int i = 0; i < rendererList.size(); ++i)
    {
		switch (rendererList[i]->GetType())
		{
		case RenderType::Sprite:
		{
			if (rendererList[i]->remove)
			{
				delete rendererList[i];
				rendererList.erase(rendererList.begin() + i);
				--i;
				continue;
			}

			if (!rendererList[i]->IsActive() || !rendererList[i]->Owner()->IsActive())
				continue;

			SpriteRenderer* spriteRenderer = (SpriteRenderer*)rendererList[i];

			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetTransparency(1.0f);

			float halfWidth = spriteRenderer->GetHalfWidth();
			float halfHeight = spriteRenderer->GetHalfHeight();
			halfWidth *= spriteRenderer->GetTransform()->worldscale.x;
			halfHeight *= spriteRenderer->GetTransform()->worldscale.y;

			Transform* transform = spriteRenderer->GetTransform();

			float rotationAngle = transform->worldrotation;
			Vector2 BottomLeft = Vector2(halfWidth, -halfHeight);
			Vector2 BottomRight = Vector2(-halfWidth, -halfHeight);
			Vector2 TopLeft = Vector2(halfWidth, halfHeight);
			Vector2 TopRight = Vector2(-halfWidth, halfHeight);

			BottomLeft.Rotate(rotationAngle);
			BottomRight.Rotate(rotationAngle);
			TopLeft.Rotate(rotationAngle);
			TopRight.Rotate(rotationAngle);

			AEGfxSetPosition(transform->worldposition.x, transform->worldposition.y);

			// Scale and Rotate Matrix
			float cosAngle = cosf(rotationAngle / 180.0f * 3.1415926535897932384626433832795f);
			float sinAngle = sinf(rotationAngle / 180.0f * 3.1415926535897932384626433832795f);
			float width = halfWidth * 2;
			float height = halfHeight * 2;
			// Multiply Matrix by scale according to the GameObject Size then by rotation
			float TransformMatrix[3][3]{
				{cosAngle * width,sinAngle * height,transform->worldposition.x},
				{-sinAngle * width,cosAngle * height,transform->worldposition.y},
				{0,0,1}
			};

			AEGfxSetTransform(TransformMatrix);

			AEGfxSetTintColor(spriteRenderer->R, spriteRenderer->G, spriteRenderer->B, spriteRenderer->GetTransparency());
			//AEGfxSetTextureMode(AE_GFX_TM_PRECISE); Different quality if using average
			AEGfxTextureSet(AssetManager.GetTexture(spriteRenderer->GetTextureName()), 0, 0);
			AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
		}
			break;
		case RenderType::Font:
		{
			if (rendererList[i]->remove)
			{
				delete rendererList[i];
				rendererList.erase(rendererList.begin() + i);
				--i;
				continue;
			}

			if (!rendererList[i]->IsActive() || !rendererList[i]->Owner()->IsActive())
				continue;

			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			TextRenderer* textRenderer = (TextRenderer*)rendererList[i];

			Transform* transform = textRenderer->GetTransform();
			int linecount = 0;
			int start = 0;
			string tempTextString = textRenderer->GetText();
			float textheight = textRenderer->GetTextHeight();
			float textwidth = textRenderer->GetTextWidth();
			for (int x = 0; char c = tempTextString[x]; x++) {
				if (c == '\n') {
					tempTextString[x] = '\0';
					AEGfxPrint(AssetManager.GetFont(textRenderer->GetFontName()), &tempTextString[start],
						(transform->worldposition.x - textwidth / 2) / ((float)AEGetWindowWidth() / 2),
						(transform->worldposition.y - textheight / 2 - linecount * (textheight + textRenderer->GetLineBuffer())) / ((float)AEGetWindowHeight() / 2),
						textRenderer->GetScale(), textRenderer->TextR, textRenderer->TextG, textRenderer->TextB);
					linecount++;
					start = x + 1;
				}

			}
			//Text Rendering
			AEGfxPrint(AssetManager.GetFont(textRenderer->GetFontName()), &tempTextString[start],
				(transform->worldposition.x - textwidth / 2) / ((float)AEGetWindowWidth() / 2),
				(transform->worldposition.y - textheight / 2 - linecount * (textheight + textRenderer->GetLineBuffer())) / ((float)AEGetWindowHeight() / 2),
				textRenderer->GetScale(), textRenderer->TextR, textRenderer->TextG, textRenderer->TextB);
		}

			break;
		case RenderType::Line:

			break;
		default:
			break;
		}
	}
}

void _renderer::AddToList(RenderComponent* entry)
{
    rendererList.push_back(entry);

	//Sort algorithm
}

void _renderer::FreeAll(void)
{
	rendererList.clear();
}

#include "Renderer.h"
#include "LineRenderer.h"

_renderer::_renderer()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00FF00FF, 0.0f, 1.0f, //bottom left
		0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f, //bottom right
		-0.5f, 0.5f, 0x0000FFFF, 0.0f, 0.0f); //top left

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFFFF, 1.0f, 1.0f,  //bottom right
		0.5f, 0.5f, 0x00FFFFFF, 1.0f, 0.0f,	//top right
		-0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f); //top left

	mesh = AEGfxMeshEnd();
}

_renderer::~_renderer()
{
	//AEGfxMeshFree(mesh);
}

_renderer& _renderer::Instance(void)
{
	static _renderer instance;
    return instance;
}

void _renderer::Update(void)
{
    for (int i = 0; i < rendererList.size(); ++i)
    {
		if (rendererList[i]->remove)
		{
			delete rendererList[i];
			rendererList.erase(rendererList.begin() + i);
			--i;
			continue;
		}

		if (!rendererList[i]->IsActive() || !rendererList[i]->Owner()->IsActive() ||
			(rendererList[i]->Owner()->GetParent() != NULL && !rendererList[i]->Owner()->GetParent()->Owner()->IsActive()))
			continue;

		switch (rendererList[i]->GetType())
		{
		case RenderType::Sprite:
		{
			SpriteRenderer* spriteRenderer = (SpriteRenderer*)rendererList[i];

			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

			switch (spriteRenderer->GetBlendMode())
			{
			case 0:
				AEGfxSetBlendMode(AE_GFX_BM_NONE);
				break;
			case 1:
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				break;
			case 2:
				AEGfxSetBlendMode(AE_GFX_BM_ADD);
				break;
			case 3:
				AEGfxSetBlendMode(AE_GFX_BM_NUM);
				break;
			default:
				AEGfxSetBlendMode(AE_GFX_BM_NONE);
				break;
			}

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

			BottomLeft.RotateAC(rotationAngle);
			BottomRight.RotateAC(rotationAngle);
			TopLeft.RotateAC(rotationAngle);
			TopRight.RotateAC(rotationAngle);

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
			AEGfxSetTextureMode(AE_GFX_TM_PRECISE); //Different quality if using average
			Vector2 temp = spriteRenderer->GetTextureOffset();
			AEGfxTextureSet(AssetManager.GetTexture(spriteRenderer->GetTextureName()), temp.x, temp.y);
			AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
		}
			break;
		case RenderType::Font:
		{
			TextRenderer* textRenderer = (TextRenderer*)rendererList[i];
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			textRenderer->CalculateTextSize();
			Transform* transform = textRenderer->GetTransform();
			int linecount = 0;
			int start = 0;
			string tempTextString = textRenderer->GetText();
			float textheight = textRenderer->GetTextHeight();
			float textwidth = textRenderer->GetTextWidth();

			if (textRenderer->GetWarpAround()) {
				WrapAround(textRenderer);
				textRenderer->SetWarpAround(false);
				tempTextString = textRenderer->GetText();
			}
				
			for (int x = 0; char c = tempTextString[x]; x++) {
				if (c == '\n') {
					tempTextString[x] = '\0';
					AEGfxPrint(AssetManager.GetFont(textRenderer->GetFontName()), &tempTextString[start],
						TextAlignmentX(textRenderer) / ((float)AEGetWindowWidth() / 2),
						(TextAlignmentY(textRenderer) - linecount * (textheight + textRenderer->GetLineBuffer())) / ((float)AEGetWindowHeight() / 2),
						textRenderer->GetFontScale(), textRenderer->textR, textRenderer->textG, textRenderer->textB);
					linecount++;
					start = x + 1;
				}

			}
			//Text Rendering
			AEGfxPrint(AssetManager.GetFont(textRenderer->GetFontName()), &tempTextString[start],
				TextAlignmentX(textRenderer) / ((float)AEGetWindowWidth() / 2),
				(TextAlignmentY(textRenderer) - linecount * (textheight + textRenderer->GetLineBuffer())) / ((float)AEGetWindowHeight() / 2),
				textRenderer->GetFontScale(), textRenderer->textR, textRenderer->textG, textRenderer->textB);
		}
			break;
		case RenderType::Line:
		{
			LineRenderer* lineRenderer = (LineRenderer*)rendererList[i];
			for (int i = 0; i < lineRenderer->lineList.size(); i++)
				AEGfxMeshDraw(lineRenderer->lineList[i], AE_GFX_MDM_LINES_STRIP);
		}
			break;
		default:
			break;
		}
	}
}

float _renderer::TextAlignmentX(TextRenderer* textRenderer) {
	SpriteRenderer* tempSR = textRenderer->Owner()->GetComponent<SpriteRenderer>();
	switch (textRenderer->GetXAlignment())
	{
	case TextRenderer::xAlignmentTypes::Left:
		return (textRenderer->GetTransform()->worldposition.x - tempSR->GetHalfWidth() + textRenderer->GetXBuffer());
		break;
	case TextRenderer::xAlignmentTypes::Right:
		return (textRenderer->GetTransform()->worldposition.x + tempSR->GetHalfWidth() - textRenderer->GetTextWidth() - textRenderer->GetXBuffer());
		break;
	case TextRenderer::xAlignmentTypes::Mid:
		return (textRenderer->GetTransform()->worldposition.x - textRenderer->GetTextWidth() / 2);;
		break;
	default:
		return 0;
		break;
	}
}
float _renderer::TextAlignmentY(TextRenderer* textRenderer) {
	SpriteRenderer* tempSR = textRenderer->Owner()->GetComponent<SpriteRenderer>();
	switch (textRenderer->GetYAlignment())
	{
	case TextRenderer::yAlignmentTypes::Top:
		return (textRenderer->GetTransform()->worldposition.y + tempSR->GetHalfHeight() - textRenderer->GetTextHeight() - textRenderer->GetYBuffer());
		break;
	case TextRenderer::yAlignmentTypes::Bottom:
		return (textRenderer->GetTransform()->worldposition.y - tempSR->GetHalfHeight() + textRenderer->GetYBuffer());
		break;
	case TextRenderer::yAlignmentTypes::Mid:
		return (textRenderer->GetTransform()->worldposition.y - textRenderer->GetTextHeight() / 2);
		break;
	default:
		return 0;
		break;
	}
}

void  _renderer::WrapAround(TextRenderer* textRenderer) {
	SpriteRenderer* tempSR = textRenderer->Owner()->GetComponent<SpriteRenderer>();
	float length = (textRenderer->GetTransform()->worldposition.x + tempSR->GetHalfWidth()) - TextAlignmentX(textRenderer) - textRenderer->GetXBuffer();
	float textScale = textRenderer->GetFontScale();
	float alteredStringLength = 0;
	float wordWidth = 0;
	float wordHeight = 0;
	string tempTextString = textRenderer->GetText();
	string alteredString = "";
	string word = "";
	char tempChar = 0;

	for (string::iterator it = tempTextString.begin(); it != tempTextString.end(); ++it) {
		tempChar = *it;
		word.append(1, tempChar);
		if (isspace(tempChar) || it == tempTextString.end()-1) {
			if (tempChar == '\n') {
				alteredString.replace(alteredString.end()-1, alteredString.end(), 1, tempChar);
			}
			else{
				AEGfxGetPrintSize(AssetManager.GetFont(textRenderer->GetFontName()), &word[0], textScale, wordWidth, wordHeight);
				wordWidth = wordWidth * ((float)AEGetWindowWidth() / 2.0f);
				if ((alteredStringLength + wordWidth) > length) {
					alteredString.replace(alteredString.end()-1, alteredString.end(), 1,'\n');
					alteredString.append(word);
					alteredStringLength = wordWidth;
				}
				else {
					alteredString.append(word);
				}
				alteredStringLength = alteredStringLength + wordWidth;
				word.clear();
			}
		}
	}
	textRenderer->SetText(alteredString);
}

void _renderer::AddToList(RenderComponent* entry)
{
    rendererList.push_back(entry);
	InsertionSort();
}

int _renderer::binarySearch(vector<RenderComponent*> a, int item, int low, int high)
{
	if (high <= low)
		return (item > a[low]->GetLayer()) ?
		(low + 1) : low;

	int mid = (low + high) / 2;

	if (item == a[mid]->GetLayer())
		return mid + 1;

	if (item > a[mid]->GetLayer())
		return binarySearch(a, item,
			mid + 1, high);
	return binarySearch(a, item, low,
		mid - 1);
}

void _renderer::InsertionSort(void)
{
	int i, loc, j;

	RenderComponent* selected;

	for (i = 1; i < rendererList.size(); ++i)
	{
		j = i - 1;
		selected = rendererList[i];

		// find location where selected should be inseretd
		loc = binarySearch(rendererList, selected->GetLayer(), 0, j);

		// Move all elements after location to create space
		while (j >= loc)
		{
			rendererList[(size_t)j + 1] = rendererList[j];
			j--;
		}
		rendererList[(size_t)j + 1] = selected;
	}
}

void _renderer::FreeRenderComponents(void)
{
	for (int i = 0; i < rendererList.size(); ++i)
		delete  rendererList[i];
	rendererList.clear();
}

void _renderer::FreeMesh(void)
{
	AEGfxMeshFree(mesh);
}

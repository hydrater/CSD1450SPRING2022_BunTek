#include "TextRenderer.h"
#include "AssetManager.h"

TextRenderer::TextRenderer(void)
{
	AssetManager.AddToTextList(this);
}

TextRenderer::~TextRenderer(void)
{

}

Transform* TextRenderer::GetTransform(void)
{
	return this->Owner()->transform;
}


string TextRenderer::GetFontName(void)
{
	return fontString;
}

void TextRenderer::SetFont(string fontName)
{
	fontString = fontName;
}
string TextRenderer::GetText(void)
{
	return text;
}

void TextRenderer::SetText(string _text)
{
	text = _text;

}

vector<float> TextRenderer::GetTextColor(void)
{
	return vector<float>{TextR, TextG, TextB};
}

void TextRenderer::SetTextColor(float _R, float _G, float _B)
{
	TextR = _R, TextG = _G, TextB = _B;
}

void TextRenderer::ScaleTexture(SpriteRenderer* sr) {
	AEGfxGetPrintSize(AssetManager.GetFont(fontString), &text[0], textScale, TextWidth, TextHeight);
	TextWidth = TextWidth * (float)AEGetWindowWidth() / 2;
	TextHeight = TextHeight * (float)AEGetWindowHeight() / 2;
	float width = sr->GetHalfWidth();
	float height = sr->GetHalfHeight();
	if (TextWidth / 2 > width) {
		width = TextWidth / 2 + buffer;
	}
	if (TextHeight / 2 > height) {
		height = TextHeight / 2 + buffer;
	}
	sr->Size(width*2, height*2);
}
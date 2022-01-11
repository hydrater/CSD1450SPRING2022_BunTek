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

void TextRenderer::SetScale(float _scale)
{
	textScale = _scale;
}

float TextRenderer::GetScale(void) {
	return textScale;
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
void TextRenderer::SetTextWidth(float _TextWidth) {
	textWidth = _TextWidth;
}
void TextRenderer::SetTextHeight(float _TextHeight) {
	textHeight = _TextHeight;
}
float TextRenderer::GetTextWidth(void) {
	return textWidth;
}
float TextRenderer::GetTextHeight(void) {
	return textHeight;
}
void TextRenderer::SetBuffer(float _Buffer) {
	buffer = _Buffer;
}
void TextRenderer::SetLineBuffer(float _LineBuffer) {
	lineBuffer = _LineBuffer;
}
float TextRenderer::GetBuffer(void) {
	return buffer;
}
float TextRenderer::GetLineBuffer(void) {
	return lineBuffer;
}
void TextRenderer::SetTextColor(float _R, float _G, float _B)
{
	TextR = _R, TextG = _G, TextB = _B;
}

void TextRenderer::ScaleTexture(SpriteRenderer* sr) {
	AEGfxGetPrintSize(AssetManager.GetFont(fontString), &text[0], textScale, textWidth, textHeight);
	textWidth = textWidth * (float)AEGetWindowWidth() / 2;
	textHeight = textHeight * (float)AEGetWindowHeight() / 2;
	float width = sr->GetHalfWidth();
	float height = sr->GetHalfHeight();
	if (textWidth / 2 > width) {
		width = textWidth / 2 + buffer;
	}
	if (textHeight / 2 > height) {
		height = textHeight / 2 + buffer;
	}
	sr->Size(width*2, height*2);
}
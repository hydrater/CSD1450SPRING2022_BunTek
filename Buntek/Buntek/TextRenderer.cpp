#include "TextRenderer.h"
#include "Renderer.h"


TextRenderer::TextRenderer(void)
{
	SetType(1);
	Renderer.AddToList(this);
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

void TextRenderer::SetFontScale(float _scale)
{
	textScale = _scale;
}

float TextRenderer::GetFontScale(void) {
	return textScale;
}
void TextRenderer::SetFontSize(float _fontsize) {
	textScale = _fontsize / AssetManager.GetdefaultFontSize();
}
float TextRenderer::GetFontSize(void) {
	return textScale * AssetManager.GetdefaultFontSize();
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
	return vector<float>{textR, textG, textB};
}

void TextRenderer::SetTextWidth(float _TextWidth, int lineNum) {
	if (lineNum >= textWidthList.size()) {
		textWidthList.push_back(_TextWidth);
	}
	else
	{
		textWidthList[lineNum] = _TextWidth;
	}
	
}
void TextRenderer::SetTextHeight(float _TextHeight) {
	textHeight = _TextHeight;
}
float TextRenderer::GetTextWidth(int lineNum) {
	return textWidthList[lineNum];
}
float TextRenderer::GetTextHeight(void) {
	return textHeight;
}
void TextRenderer::SetXBuffer(float _xBuffer) {
	xbuffer = _xBuffer;
}
void TextRenderer::SetYBuffer(float _yBuffer) {
	ybuffer = _yBuffer;
}
void TextRenderer::SetLineBuffer(float _LineBuffer) {
	lineBuffer = _LineBuffer;
}
float TextRenderer::GetXBuffer(void) {
	return xbuffer;
}
float TextRenderer::GetYBuffer(void) {
	return ybuffer;
}
float TextRenderer::GetLineBuffer(void) {
	return lineBuffer;
}
void TextRenderer::SetTextColor(float _R, float _G, float _B)
{
	textR = _R, textG = _G, textB = _B;
}

void TextRenderer::SetXAlignment(xAlignmentTypes _xAlignment) {
	xAlignment = _xAlignment;
}
void TextRenderer::SetYAlignment(yAlignmentTypes _yAlignment) {
	yAlignment = _yAlignment;
}
TextRenderer::xAlignmentTypes TextRenderer::GetXAlignment(void) {
	return xAlignment;
}
TextRenderer::yAlignmentTypes TextRenderer::GetYAlignment(void) {
	return yAlignment;
}

void TextRenderer::CalculateTextSize(void) {
	if (textWidthList.size() == 1) {
		AEGfxGetPrintSize(AssetManager.GetFont(fontString), &text[0], textScale, textWidthList[0], textHeight);
		textWidthList[0] = textWidthList[0] * (float)AEGetWindowWidth() / 2.0f;
		textHeight = textHeight * (float)AEGetWindowHeight() / 2.0f;
	}
}

void TextRenderer::ScaleTexture(SpriteRenderer* sr) {
	CalculateTextSize();
	float width = sr->GetHalfWidth();
	float height = sr->GetHalfHeight();
	float maxTextWidth = 0;
	for (size_t i = 0; i < textWidthList.size(); ++i) {
		if (maxTextWidth < textWidthList[i]) {
			maxTextWidth = textWidthList[i];
		}
	}
	if (maxTextWidth / 2 > width) {
		width = maxTextWidth / 2 + xbuffer;
	}
	if (textHeight / 2 > height) {
		height = textHeight / 2 + ybuffer;
	}
	sr->Size(width*2, height*2);
}

void TextRenderer::SetWarpAround(bool _warparound) {
	warparound = _warparound;
}
bool TextRenderer::GetWarpAround(void) {
	return warparound;
}
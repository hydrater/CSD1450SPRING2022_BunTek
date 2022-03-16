#pragma once
#include <string>
#include "Transform.h"
#include "RenderComponent.h"
#include "SpriteRenderer.h"

class TextRenderer : public RenderComponent
{
public:
	TextRenderer(void);
	~TextRenderer(void);

	enum class xAlignmentTypes:char {
		Mid = 0,
		Left = 1,
		Right = 2
	};

	enum class yAlignmentTypes:char{
		Mid = 0,
		Top = 1,
		Bottom = 2
	};

	Transform* GetTransform(void);
	string GetFontName(void);
	void SetFont(string textureName);
	void SetFontScale(float _scale);
	float GetFontScale(void);
	void SetFontSize(float _fontsize);
	float GetFontSize(void);
	string GetText(void);
	void SetText(string text);
	void SetTextWidth(float _TextWidth, int lineNum);
	void SetTextHeight(float _TextHeight);
	float GetTextWidth(int lineNum);
	float GetTextHeight(void);
	void SetXBuffer(float _Buffer);
	void SetYBuffer(float _Buffer);
	void SetLineBuffer(float _LineBuffer);
	float GetXBuffer(void);
	float GetYBuffer(void);
	float GetLineBuffer(void);
	vector<float> GetTextColor(void);
	// 0.0f to 1.0f 
	void SetTextColor(float _R, float _G, float _B);
	void ScaleTexture(SpriteRenderer* sr);
	float textR = 1, textG = 1, textB = 1;
	void CalculateTextSize(void);
	void SetXAlignment(xAlignmentTypes _xAlignment);
	void SetYAlignment(yAlignmentTypes _yAlignment);
	xAlignmentTypes GetXAlignment(void);
	yAlignmentTypes GetYAlignment(void);
	
	void SetWarpAround(bool _warparound);
	bool GetWarpAround(void);
	int lineCount = 1;
private:
	string fontString = "EquinoxB.otf";
	float textScale = 1;
	string text = "";
	vector<float> textWidthList{0};
	float textHeight = 0;
	float xbuffer = 10;
	float ybuffer = 10;
	float lineBuffer = 10;
	bool warparound = false;
	xAlignmentTypes xAlignment = TextRenderer::xAlignmentTypes::Mid;
	yAlignmentTypes yAlignment = TextRenderer::yAlignmentTypes::Mid;


};
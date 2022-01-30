#pragma once
#include "RenderComponent.h"

class LineRenderer : public RenderComponent
{
private:
	LineRenderer(void);
	~LineRenderer(void);

public:
	vector<AEGfxVertexList*> lineList;
	void Add(Vector2 pos, Vector2 pos2);
};

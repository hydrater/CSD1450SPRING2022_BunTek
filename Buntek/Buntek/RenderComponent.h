#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Component.h"

enum class RenderType : short
{
	Sprite = 0,
	Font = 1,
	Line = 2
};

class RenderComponent : public Component
{
public:
	RenderComponent();
	~RenderComponent();

	void SetLayer(short _layer);
	short GetLayer(void);
	void SetType(short _type);
	RenderType GetType(void);
private:
	void SortList(void);
	short layer = 0;
	RenderType type = RenderType::Sprite;
};

#endif
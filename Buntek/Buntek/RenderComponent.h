#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent();
	~RenderComponent();

	void SetLayer(short _layer);
	short GetLayer(void);
private:
	short layer = 0;
};

#endif
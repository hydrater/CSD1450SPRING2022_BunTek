#include "Renderer.h"

_renderer* _renderer::instance = 0;

_renderer::_renderer()
{
}

_renderer::~_renderer()
{
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
    for (int i = 0; i < RenderList.size(); ++i)
    {
        //RenderList[i].
    }
}

void _renderer::AddTolist(RenderComponent* entry)
{
    RenderList.push_back(entry);
}

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
    for (int i = 0; i < renderList.size(); ++i)
    {
        switch (renderList[i]->GetType())
        {
        case RenderType::Sprite:

            break;
        case RenderType::Font:

            break;
        case RenderType::Line:

            break;
        default:
            break;
        }
    }
}

void _renderer::AddTolist(RenderComponent* entry)
{
    renderList.push_back(entry);
}

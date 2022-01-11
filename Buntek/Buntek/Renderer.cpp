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

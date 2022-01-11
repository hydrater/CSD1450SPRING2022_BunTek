#include "Renderer.h"

_Renderer* _Renderer::instance = 0;

_Renderer::_Renderer()
{
}

_Renderer::~_Renderer()
{
}

_Renderer& _Renderer::Instance(void)
{
    if (instance != 0)
        return *instance;
    instance = new _Renderer();

    return *instance;
}

#pragma once
#include <AEEngine.h>
#include <vector>
#include <map>
#include "AssetManager.h"

#define Renderer _renderer::Instance()

class _renderer
{
private:
    static _renderer* instance;
    _renderer();
    ~_renderer();

public:
    static _renderer& Instance(void);
};

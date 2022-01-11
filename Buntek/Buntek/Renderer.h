#pragma once
#include <AEEngine.h>
#include <vector>
#include <map>
#include "AssetManager.h"
#include "RenderComponent.h"

#define Renderer _renderer::Instance()

class _renderer
{
private:
    static _renderer* instance;
    _renderer();
    ~_renderer();
    vector<RenderComponent*> RenderList;

public:
    static _renderer& Instance(void);
    void Update(void);
    void AddTolist(RenderComponent* entry);
};

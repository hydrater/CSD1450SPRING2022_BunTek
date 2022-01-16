#pragma once
#include <vector>
#include <string>
using namespace std;

#define ArtifactDatabase _artifactdatabase::Instance()



class _artifactdatabase
{
private:
    static _artifactdatabase* instance;
    _artifactdatabase();
    ~_artifactdatabase();

public:
    static _artifactdatabase& Instance(void);

};
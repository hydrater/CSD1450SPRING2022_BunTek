#include "ArtifactDatabase.h"

_artifactdatabase* _artifactdatabase::instance = 0;


_artifactdatabase::_artifactdatabase()
{

}

_artifactdatabase::~_artifactdatabase()
{

}

_artifactdatabase& _artifactdatabase::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _artifactdatabase();
    return *instance;
}
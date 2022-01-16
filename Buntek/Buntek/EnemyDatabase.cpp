#include "EnemyDatabase.h"

_enemydatabase* _enemydatabase::instance = 0;


_enemydatabase::_enemydatabase()
{

}

_enemydatabase::~_enemydatabase()
{

}

_enemydatabase& _enemydatabase::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _enemydatabase();
    return *instance;
}
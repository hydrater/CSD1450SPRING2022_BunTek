#include "EnemyDatabase.h"

_enemydatabase::_enemydatabase()
{

}

_enemydatabase::~_enemydatabase()
{

}

_enemydatabase& _enemydatabase::Instance(void)
{
    static _enemydatabase instance;
    return instance;
}
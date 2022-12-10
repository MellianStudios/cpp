#ifndef MELLIANCORE_BLIZZARDLOADER_H
#define MELLIANCORE_BLIZZARDLOADER_H

#include "WDBC.h"

class BlizzardLoader
{
public:
    static void load()
    {
        WDBC::loadAll();
    }
};

#endif //MELLIANCORE_BLIZZARDLOADER_H

#include <iostream>
#include <vector>
#include "BlizzardLoader/BlizzardLoader/BlizzardLoader.h"

int main()
{
    std::cout << "world server running" << std::endl;

    BlizzardLoader::load();

    return 0;
}

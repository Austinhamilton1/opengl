#include "opencl/Platform.h"

#include <vector>
#include <iostream>

int main() {
    std::vector<cl::Platform> allPlatforms = cl::Platform::allPlatforms();
    auto defaultPlatform = allPlatforms[0];

    std::cout << "Using platform " << defaultPlatform.getInfo<CL_PLATFORM_NAME, char>() << std::endl;
}
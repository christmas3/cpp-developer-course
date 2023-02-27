#include "lib.h"

#include <iostream>

int main(int, char**) {
    std::cout << "Version: " << version_lib::version() << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

cmake_minimum_required(VERSION 3.22)

set(BUILD_VERSION "1" CACHE INTERNAL "Build version")
set(PROJECT_BUILD_VERSION ${BUILD_VERSION})

project(helloworld VERSION 0.0.${PROJECT_BUILD_VERSION})

find_package(GTest CONFIG REQUIRED)

configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)

set_target_properties(helloworld_cli helloworld PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

target_include_directories(helloworld
        PRIVATE "${CMAKE_BINARY_DIR}"
        )

target_link_libraries(helloworld_cli PRIVATE
        helloworld
        )
target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
        )
target_compile_options(helloworld PRIVATE
        -Wall -Wextra -pedantic -Werror
        )

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

enable_testing()
add_subdirectory(test)

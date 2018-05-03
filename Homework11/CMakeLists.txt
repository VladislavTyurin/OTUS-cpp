cmake_minimum_required(VERSION 3.2)
project(async VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

configure_file(version.h.in version.h)

add_library(async SHARED async.cpp async.h Context.cpp Context.h StringHandler.cpp StringHandler.h Bulk.cpp Bulk.h Writer.h)
add_executable(async_cli main.cpp)

set_target_properties(async PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        COMPILE_FLAGS -pthread
        LINK_FLAGS -pthread
        )

set(CMAKE_CXX_FLAGS "-std=c++11")
target_link_libraries(async_cli async)

install(TARGETS async DESTINATION lib)
install(TARGETS async_cli DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT vst123@yandex.ru)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")

include(CPack)

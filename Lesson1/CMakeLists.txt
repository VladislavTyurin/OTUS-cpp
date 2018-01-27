cmake_minimum_required(VERSION 3.2)

project(Lesson1 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(Lesson1_cli main.cpp)

add_executable(test_version_cli test_version.cpp)

add_library(lesson1 lib.cpp)

set_target_properties(Lesson1_cli lesson1 test_version_cli PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

set_target_properties(test_version_cli PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
        )

target_link_libraries(Lesson1_cli lesson1)

target_link_libraries(test_version_cli
        ${Boost_LIBRARIES}
        lesson1)

install(TARGETS Lesson1_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT vst123@yandex.ru)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")

include(CPack)

enable_testing()

add_test(test_version test_version_cli)
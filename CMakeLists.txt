cmake_minimum_required(VERSION 3.5)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    project(Allocator VERSION 1.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project(Allocator VERSION 1.0.1)
endif()



set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
include_directories(${SOURCE_PATH})
add_library(my_list ${SOURCE_PATH}/MyList.cpp ${SOURCE_PATH}/Allocator.h ${SOURCE_PATH}/MyList.h)
# find packages
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# target version_lib
configure_file(${SOURCE_PATH}/version.h.in version.h)
add_library(version_lib ${SOURCE_PATH}/version.cpp)
target_include_directories(version_lib
    PUBLIC "${CMAKE_BINARY_DIR}"
)
target_compile_options(version_lib PRIVATE
    -Wall -Wextra -pedantic -Werror
)


add_executable(allocator ${SOURCE_PATH}/main.cpp)

target_link_libraries(allocator my_list)

set_target_properties(allocator PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
        
        
install(TARGETS allocator RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEB_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${allocator_VERSION})
set(CPACK_PACKAGE_CONTACT buevichd@yandex-team.ru)
include(CPack)

cmake_minimum_required(VERSION 3.10)

# Project name
set(PATCH_VERSION "0" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
project(allocator VERSION ${PROJECT_VESRION})

# Include lib conan test
if(TEST)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

# Options
set(CMAKE_CXX_STANDARD 17)

# Source files
set(SOURCES
    source/main.cpp
    source/my_allocator.cpp
    include/my_allocator.h
)

# Source tests files
set(TEST_SOURCES
    test/source/test_allocator.cpp
    source/my_allocator.cpp
    include/my_allocator.h
)

# Include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

# Set build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

# Compiling target
add_executable(${PROJECT_NAME} ${SOURCES})

if(TEST)
    # Compiling target for tests
    add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

    # Link target with gtest
    target_link_libraries(${PROJECT_NAME}_tests ${CONAN_LIBS})
    
    # CI\CD
    add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)
    enable_testing()
endif()

if(DEBPACK)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
    set(CPACK_GENERATOR DEB)
    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
    set(CPACK_PACKAGE_CONTACT karasev.ia@phystech.edu)
    include(CPack)
endif()

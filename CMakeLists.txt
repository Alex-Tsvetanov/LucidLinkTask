cmake_minimum_required(VERSION 3.18)
project("NumberOfComponentsInAMatrix"
    VERSION 1.0.0.0
    DESCRIPTION "Find the number of components of marked cells within a table if a component consists of all cells that have a common side with at least one other cell from the same component"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(WITH_PLAYGROUND "Compile stdio testing source" ON)
option(WITH_TESTS "Compile tests as part of ALL_BUILD" ON)
option(AS_MATRIX "Compile solution which takes a boolean matrix as an argument" ON)
option(AS_LIST "Compiles solution which takes the matrix as a list of marked cells" ON)
option(COORD_32BIT "Compiles the solution for matrixes up to 2^32 by 2^32" ON)

if(AS_MATRIX)
    add_compile_definitions(-DAS_MATRIX)
endif()

if(AS_LIST)
    add_compile_definitions(-DAS_LIST)
endif()

if(COORD_32BIT)
    add_compile_definitions(-DCOORD_32BIT)
endif()

add_subdirectory(src)

if(WITH_PLAYGROUND)
    add_subdirectory(playground)
endif()

if(WITH_TESTS)
    enable_testing()
    include(CTest)
    add_subdirectory(tests)
endif()

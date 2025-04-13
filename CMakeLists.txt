cmake_minimum_required(VERSION 3.22)
project(P3)

set(CMAKE_CXX_STANDARD 14)

#set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror") # remove -Wall if you don't want as many warnings treated as errors
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

set(SOURCES src/Graph/Cell.h
        src/Graph/Position.h
        src/Graph/Edge.h
        src/Graph/Graph.h
        src/Graph/Graph.cpp
        src/Graph/Cell.cpp
        src/Maze/Maze.h
        src/Tools/Random/Random.cpp
        src/Maze/Prim.cpp
        src/Maze/Prim.h
        src/Tools/Array2D/Array2D.h
        src/Tools/Array2D/CellArray2D.h
        src/Tools/Array2D/CellArray2D.cpp
)

add_executable(P3 src/Maze/Example/main.cpp
        ${SOURCES}
)

add_executable(A-Star src/TraversalAlgorithms/A-star/Example/main.cpp
        ${SOURCES}
        src/TraversalAlgorithms/A-star/A_Star.h
        src/TraversalAlgorithms/A-star/A_Star.cpp
)
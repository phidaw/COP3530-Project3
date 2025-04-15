cmake_minimum_required(VERSION 3.22)
project(P3)

set(CMAKE_CXX_STANDARD 14)

# compile programs with std::thread support
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

#set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror") # remove -Wall if you don't want as many warnings treated as errors
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

set(TEST src/Maze/Example/PrintMaze.h
        src/Traversal/Algorithms/A-star/Example/PrintAStar.h)

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
        src/Traversal/Algorithms/A-star/A_Star.h
        src/Traversal/Algorithms/A-star/A_Star.cpp
        src/Traversal/PathUtilities/PathUtilities.h
        src/Tools/MinHeap/MinHeap.h
)

add_executable(Maze src/Maze/Example/main.cpp
        ${SOURCES}
        ${TEST}
)

add_executable(A-Star src/Traversal/Algorithms/A-star/Example/main.cpp
        ${SOURCES}
        ${TEST}
        src/Traversal/Agents/AgentManager.h
)

add_executable(MazeAgents_AStar src/Traversal/Agents/Example/main.cpp
        ${SOURCES}
        ${TEST}
        src/Traversal/Agents/TraversalAgent.h
)
target_link_libraries(MazeAgents_AStar Threads::Threads)
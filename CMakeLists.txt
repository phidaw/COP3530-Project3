cmake_minimum_required(VERSION 3.22)
project(P3)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(TEST src/Maze/Example/PrintMaze.h
        src/Traversal/Algorithms/Example/PrintAStar.h
        src/Traversal/Algorithms/Example/PrintBFS.h
        src/Traversal/Algorithms/Example/PrintDijkstra.h)

set(SOURCES src/Tools/CompassDir/CompassDir.h
        src/Graph/Cell.h
        src/Graph/Cell.cpp
        src/Graph/RegionMap.h
        src/Graph/RegionMap.cpp
        src/Graph/Position.h
        src/Graph/Edge.h
        src/Graph/Graph.h
        src/Graph/Graph.cpp
        src/Maze/Maze.h
        src/Tools/Random/Random.cpp
        src/Maze/Prim.cpp
        src/Maze/Prim.h
        src/Tools/Array2D/Array2D.h
        src/Tools/Array2D/CellArray2D.h
        src/Traversal/Algorithms/A-star/A_Star.h
        src/Traversal/Algorithms/A-star/A_Star.cpp
        src/Traversal/PathUtilities/PathUtilities.h
        src/Tools/RadixHeap/RadixHeapDouble.cpp
        src/Tools/RadixHeap/RadixHeapDouble.h
        src/Tools/RadixHeap/RadixHeapTriple.cpp
        src/Tools/RadixHeap/RadixHeapTriple.h
        src/Traversal/Algorithms/Dijsktras/Dijkstra.cpp
        src/Traversal/Algorithms/BFS/BFS.h
        src/Traversal/Algorithms/BFS/BFS.cpp
)

add_executable(Maze src/Maze/Example/main.cpp
        ${SOURCES}
        ${TEST}
)

add_executable(Algorithms src/Traversal/Algorithms/Example/main.cpp
        ${SOURCES}
        ${TEST}
)

add_executable(Agents src/Traversal/Agents/Example/main.cpp
        ${SOURCES}
        ${TEST}
        src/Traversal/Agents/AgentManager.h
        src/Traversal/Agents/TraversalAgent.h
        src/Graph/Collectable.h
        src/Traversal/Agents/AStarAgent.cpp
        src/Traversal/Agents/AStarAgent.h
        src/Traversal/Agents/DijkstraAgent.cpp
        src/Traversal/Agents/DijkstraAgent.h
        src/Traversal/Agents/BFSAgent.cpp
        src/Traversal/Agents/BFSAgent.h
)
target_link_libraries(P3 sfml-graphics sfml-audio sfml-system)

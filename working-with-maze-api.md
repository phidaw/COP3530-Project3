<h2 style="text-align: center"> <b> Working With Maze API </b> </h2>

note: 
- As of now, mazes larger than 30x30 generate _really_ slowly. So work with mazes with a size less than that for now, until I get around to doing optimizations.

### Visuals
---
- note: graph is a square matrix
	- for <100,000 cells, cellsPerRow >=317
	- for <100,000 vertices, cellsPerRow >=316
- when printing edges to screen,  
    - go through each edge in maze, and use its position members' coordinates  
    - or, go through each cell in graph and print a cell's edge if its in the maze
- when drawing paths of agents, use mid-point of cell sprite (there's no position object at center of cells)

### Traversal Algorithms
---
- when traversing maze,  
	- traverse through cells of graph  
		- traverse through neighbors of current cell
			- select edge shared between cell and neighbor and check if its in maze edge set  
			- if the edge is not in maze's set, then there is a path between the current cell and the current neighbor
			- if there is a path, add neighbor to the "open" collection
		- collect all open neighbors, and determine which neighbor to travel to based on algorithm specifics

- the weights for cells will use their positions
	- calculate manhattan distance between two cell positions
	- then use the result for determining which cell to go to based on algorithm specifics
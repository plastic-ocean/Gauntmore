//#include "Map.h"
//
//
///**
// * Adds all walls to list that are adjacent to maze[i][j].
// *
// * @size is the wall list size.
// * @walls is the current list of walls.
// * @i is the i in maze[i][j].
// * @j is the j in maze[i][j].
// */
//int Map::addWall(int wallListSize, int maxWallListSize, int wallList[maxWallListSize][2], int mazeSize, char maze[mazeSize][mazeSize], int i, int j) {
//    bool onList = false;
//    for (int k = 0; k < wallListSize; ++k) {
//        if (wallList[k][0] == i && wallList[k][1] == j) {
//            onList = true;
//            break;
//        }
//    }
//    
//    if (!onList && i != 0 && i != mazeSize - 1 && j != 0 && j != mazeSize - 1 && maze[i][j] == '@') {
//        // Add wall
//        wallList[wallListSize][0] = i;
//        wallList[wallListSize][1] = j;
//        wallListSize++;
//    }
//    
//    return wallListSize;
//}
//
///**
// * Creates a 2-D maze array using Prim's algorithm for minimum spanning trees.
// *
// * @size is the size of the maze.
// * @maze is the 2-D maze array.
// */
//void Map::createMaze(int size, char maze[size][size]) {
//    // Create a 2-D array full of walls.
//    for (int i = 0; i < size; ++i) {
//        for (int j = 0; j < size; ++j) {
//            maze[i][j] = '@';
//        }
//    }
//    
//    // Create wall list.
//    int wallListSize = 0;
//    int maxWallListSize = size * size;
//    int wallList[maxWallListSize][2];
//    for (int i = 0; i < maxWallListSize; ++i) {
//        wallList[i][0] = 0;
//        wallList[i][1] = 0;
//    }
//    
//    // Create maze list.
//    int mazeListSize = 0;
//    int maxMazeListSize = size * size;
//    int mazeList[maxMazeListSize][2];
//    for (int i = 0; i < maxMazeListSize; ++i) {
//        mazeList[i][0] = 0;
//        mazeList[i][1] = 0;
//    }
//    
//    // Randomly choose an entrance, add the first floor cell, and add its walls to the wall list.
//    int edge = rand() % 3;
//    int a = 0; // entrance row
//    int b = 0; // entrance column
//    if (edge == 0) {
//        // Top
//        // #x#
//        // #.#
//        // ###
//        a = 0;
//        b = rand() % (size - 2) + 1;
//        maze[a + 1][b] = '.';
//        maze[a][b] = 'x';
//        a++;
//        
//        // Add adjacent walls.
//        wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, a + 1, b);
//        wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, a, b + 1);
//        wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, a, b - 1);
//    } else if (edge == 1) {
//        // Right
//        // ###
//        // #.x
//        // ###
//        a = rand() % (size - 2) + 1;
//        b = size - 1;
//        maze[a][b - 1] = '.';
//        maze[a][b] = 'x';
//        b--;
//        
//        // Add adjacent walls.
//        wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, a - 1, b);
//        wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, a + 1, b);
//        wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, a, b - 1);
//    } else if (edge == 2) {
//        // Bottom
//        // ###
//        // #.#
//        // #x#
//        a = size - 1;
//        b = rand() % (size - 2) + 1;
//        maze[a - 1][b] = '.';
//        maze[a][b] = 'x';
//        a--;
//        
//        // Add adjacent walls.
//        wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, a - 1, b);
//        wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, a, b + 1);
//        wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, a, b - 1);
//    } else if (edge == 3) {
//        // Left
//        // ###
//        // x.#
//        // ###
//        a = rand() % (size - 2) + 1;
//        b = 0;
//        maze[a][b + 1] = '.';
//        maze[a][b] = 'x';
//        b++;
//        
//        // Add adjacent walls.
//        wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, a - 1, b);
//        wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, a + 1, b);
//        wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, a, b + 1);
//    }
//    
//    mazeList[mazeListSize][0] = a;
//    mazeList[mazeListSize][1] = b;
//    mazeListSize++;
//    
//    int index = 0;
//    int wall[2] = {0, 0};
//    int n = 0;
//    int m = 0;
//    int count = 0;
//    
//    // While walls in wall list:
//    while (wallListSize > 1) {
//        // Get a random wall from the list.
//        index = rand() % (wallListSize - 1);
//        wall[0] = wallList[index][0];
//        wall[1] = wallList[index][1];
//        
//        // Count adjacent cells already in the maze.
//        count = 0;
//        for (int i = 0; i < mazeListSize; ++i) {
//            if ((mazeList[i][0] == wall[0] - 1 && mazeList[i][1] == wall[1]) ||
//                (mazeList[i][0] == wall[0] && mazeList[i][1] == wall[1] + 1) ||
//                (mazeList[i][0] == wall[0] + 1 && mazeList[i][1] == wall[1]) ||
//                (mazeList[i][0] == wall[0] && mazeList[i][1] == wall[1] - 1)) {
//                count++;
//            }
//        }
//        
//        // If only one of the adjacent cells is already in the maze, continue.
//        if (count == 1) {
//            // Get the cell on the opposite side of the wall.
//            n = 0; // cell row
//            m = 0; // cell column
//            if (maze[wall[0] - 1][wall[1]] == '.') {
//                // Check up
//                // ###
//                // #r#
//                // #.#
//                n = wall[0] + 1;
//                m = wall[1];
//            } else if (maze[wall[0]][wall[1] + 1] == '.') {
//                // Check right
//                // ###
//                // .r#
//                // ###
//                n = wall[0];
//                m = wall[1] - 1;
//            } else if (maze[wall[0] + 1][wall[1]] == '.') {
//                // Check down
//                // #.#
//                // #r#
//                // ###
//                n = wall[0] - 1;
//                m = wall[1];
//            } else if (maze[wall[0]][wall[1] - 1] == '.') {
//                // Check left
//                // ###
//                // #r.
//                // ###
//                n = wall[0];
//                m = wall[1] + 1;
//            }
//            
//            // Check if the cell on the opposite side of the chosen cell isn't in the maze.
//            if (maze[n][m] == '@') {
//                // Make the chosen cell part of the maze.
//                maze[wall[0]][wall[1]] = '.';
//                
//                // Add it to the maze list.
//                mazeList[mazeListSize][0] = wall[0];
//                mazeList[mazeListSize][1] = wall[1];
//                mazeListSize++;
//                
//                // Add its walls.
//                wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, wall[0] - 1, wall[1]);
//                wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, wall[0], wall[1] + 1);
//                wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, wall[0] + 1, wall[1]);
//                wallListSize = addWall(wallListSize, maxWallListSize, wallList, size, maze, wall[0], wall[1] - 1);
//            }
//        }
//        
//        // Remove the wall from the list.
//        for (int k = index; k < wallListSize; ++k) {
//            wallList[k][0] = wallList[k + 1][0];
//            wallList[k][1] = wallList[k + 1][1];
//        }
//        wallListSize--;
//    }
//    
//    // Choose random maze edge for exit.
//    int edgeList[3] = {0, 0, 0};
//    if (edge == 0) {
//        edgeList[0] = 1;
//        edgeList[1] = 2;
//        edgeList[2] = 3;
//    } else if (edge == 1) {
//        edgeList[0] = 0;
//        edgeList[1] = 2;
//        edgeList[2] = 3;
//    } else if (edge == 2) {
//        edgeList[0] = 0;
//        edgeList[1] = 1;
//        edgeList[2] = 3;
//    } else if (edge == 3) {
//        edgeList[0] = 0;
//        edgeList[1] = 1;
//        edgeList[2] = 2;
//    }
//    index = rand() % 2;
//    edge = edgeList[index];
//    
//    // Choose random exit cell from valid options.
//    int i = 0;
//    int j = 0;
//    int temp = 0;
//    index = 0;
//    int exitList[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//    int exitListSize = 0;
//    if (edge == 0) {
//        // Up
//        i = 0;
//        // j is random
//        index = 1;
//        for (int k = 1; k < size - 2; ++k) {
//            if (maze[index][k] == '.') {
//                exitList[exitListSize] = k;
//                exitListSize++;
//            }
//        }
//        temp = rand() % exitListSize;
//        j = exitList[temp];
//    } else if (edge == 1) {
//        // Right
//        // i is random
//        j = size - 1;
//        index = size - 2;
//        for (int k = 1; k < size - 2; ++k) {
//            if (maze[k][index] == '.') {
//                exitList[exitListSize] = k;
//                exitListSize++;
//            }
//        }
//        temp = rand() % exitListSize;
//        i = exitList[temp];
//    } else if (edge == 2) {
//        // Down
//        i = size - 1;
//        // j is random
//        index = size - 2;
//        for (int k = 1; k < size - 2; ++k) {
//            if (maze[index][k] == '.') {
//                exitList[exitListSize] = k;
//                exitListSize++;
//            }
//        }
//        temp = rand() % exitListSize;
//        j = exitList[temp];
//    } else if (edge == 3) {
//        // Left
//        // i is random
//        j = 0;
//        index = size - 2;
//        for (int k = 1; k < size - 2; ++k) {
//            if (maze[k][index] == '.') {
//                exitList[exitListSize] = k;
//                exitListSize++;
//            }
//        }
//        temp = rand() % exitListSize;
//        i = exitList[temp];
//    }
//    
//    // Create exit
//    maze[i][j] = '.';
//}

// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "grid.h"
#include "maze.h"
#include "mazegraphics.h"
#include "queue.h"
#include "set.h"
#include "stack.h"
#include "vector.h"
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
using namespace std;


/*
 * Generates and returns a set of valid neighboring locations for the
 * given current position in the maze.
 *
 * A neighboring location is considered valid if it is within the maze
 * boundaries and represents a traversable cell (true).
 *
 * Checks the four cardinal directions: left, right, up, and down.
 */
Set<GridLocation> generateValidMoves(Grid<bool>& maze, GridLocation cur) {

    Set<GridLocation> neighbors;
    GridLocation left = {cur.row, cur.col - 1};
    GridLocation right = {cur.row, cur.col + 1};
    GridLocation up = {cur.row - 1, cur.col};
    GridLocation down = {cur.row + 1, cur.col};

    if (maze.inBounds(left)){
        if (maze[left] == true){
            // Adding GridLocations to set, not the boolean result of maze[left]
            neighbors.add(left);
        }
    }
    if (maze.inBounds(right)){
        if (maze[right] == true){
            neighbors.add(right);
        }
    }
    if (maze.inBounds(up)){
        if (maze[up] == true){
            neighbors.add(up);
        }
    }
    if (maze.inBounds(down)){
        if (maze[down] == true){
            neighbors.add(down);
        }
    }

    return neighbors;
}

/*
 * Validates that the given path is a valid solution through the maze.
 * Checks that the path is not empty, starts at the upper-left corner,
 * ends at the bottom-right corner, consists only of valid moves,
 * and does not contain repeated locations.
 */
void validatePath(Grid<bool>& maze, Vector<GridLocation>& path) {

    // A valid path must contain at least one location.
    if (path.isEmpty()) {
        error("Path is empty!");
    }

    // The path must start at the maze entrance (row 0, column 0).
    if (path[0] != GridLocation{0, 0}) {
        error("Path does not start at the maze entrance.");
    }

    // The path must end at the maze exit (bottom-right corner).
    if (path[path.size() - 1] != GridLocation{maze.numRows() - 1,
                                              maze.numCols() - 1}) {
        error("Path does not end at the maze exit.");
    }

    Set<GridLocation> visited;

    // Check every location in the path for duplicates and valid movements.
    for (int i = 0; i < path.size(); ++i) {

        // Check whether this location has already been visited.
        if (visited.contains(path[i])) {
            error("Path contains a loop!");
        }

        // Record this location.
        visited.add(path[i]);

        // The first location has no previous location to check against.
        if (i > 0) {

            // Generate all possible valid moves from the previous location.
            Set<GridLocation> validMoves = generateValidMoves(maze, path[i - 1]);

            // Check whether the current location is a valid move.
            if (!validMoves.contains(path[i])) {
                error("Invalid move in path.");
            }
        }
    }
}

/*
 * Finds the shortest path through a maze using Breadth-First Search (BFS).
 * Maintains a queue of possible paths, exploring them in order of length.
 * Uses a Set to keep track of visited locations and avoid exploring
 * the same location more than once. Returns the first path that reaches
 * the maze exit, or an empty path if no solution is found.
 */
Vector<GridLocation> solveMazeBFS(Grid<bool>& maze) {
    drawMaze(maze);

    // 1. Create an empty queue of paths.
    Queue<Vector<GridLocation>> allPaths;

    // 2. Create the initial path containing {0, 0}.
    Vector<GridLocation> entry;
    entry.add({0, 0});

    // 3. Enqueue the initial path.
    allPaths.enqueue(entry);

    // 4. Create a collection of visited locations.
    Set<GridLocation> visited;

    // Mark {0, 0} as visited.
    visited.add({0, 0});

    // 5. While the queue isn't empty:
    while (!allPaths.isEmpty()) {

        // a. Dequeue the first path.
        Vector<GridLocation> currentPath = allPaths.dequeue();

        // b. Get its last location.
        GridLocation current = currentPath.get(currentPath.size() - 1);

        // c. If this location is the exit:
        GridLocation exit = {maze.numRows() - 1, maze.numCols() - 1};

        if (current == exit) {
            highlightPath(currentPath, "Green", 2000);
            // Return the current path.
            return currentPath;

        }

        // d. Find all valid neighboring locations.
        Set<GridLocation> neighbors = generateValidMoves(maze, current);

        // e. For each neighbor:
        for (GridLocation neighbor : neighbors) {

            // Check if this location hasn't been visited.
            if (!visited.contains(neighbor)) {

                // Mark it as visited.
                visited.add(neighbor);

                // Copy the current path.
                Vector<GridLocation> newPath = currentPath;

                // Add the neighbor to the copied path.
                newPath.add(neighbor);

                // Enqueue the new path.
                allPaths.enqueue(newPath);

                // Visualize the newly extended path.
                highlightPath(newPath, "Green", 500);
            }
        }
    }

    // 6. Return an empty path if no solution is found.
    return {};
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
Vector<GridLocation> solveMazeDFS(Grid<bool>& maze) {
    drawMaze(maze);

    // 1. Create an empty Stack of paths.
    Stack<Vector<GridLocation>> allPaths;

    // 2. Create the initial path containing {0, 0}.
    Vector<GridLocation> entry;
    entry.add({0, 0});

    // 3. push the initial path.
    allPaths.push(entry);

    // 4. Create a collection of visited locations.
    Set<GridLocation> visited;

    // Mark {0, 0} as visited.
    visited.add({0, 0});

    // 5. While the Stack isn't empty:
    while (!allPaths.isEmpty()) {

        // a. pop the first path.
        Vector<GridLocation> currentPath = allPaths.pop();

        // b. Get its last location.
        GridLocation current = currentPath.get(currentPath.size() - 1);

        // c. If this location is the exit:
        GridLocation exit = {maze.numRows() - 1, maze.numCols() - 1};

        if (current == exit) {
            highlightPath(currentPath, "Green", 2000);
            // Return the current path.
            return currentPath;

        }

        // d. Find all valid neighboring locations.
        Set<GridLocation> neighbors = generateValidMoves(maze, current);

        // e. For each neighbor:
        for (GridLocation neighbor : neighbors) {

            // Check if this location hasn't been visited.
            if (!visited.contains(neighbor)) {

                // Mark it as visited.
                visited.add(neighbor);

                // Copy the current path.
                Vector<GridLocation> newPath = currentPath;

                // Add the neighbor to the copied path.
                newPath.add(neighbor);

                // push the new path.
                allPaths.push(newPath);

                // Visualize the newly extended path.
                highlightPath(newPath, "Green", 500);
            }
        }
    }

    // 6. Return an empty path if no solution is found.
    return {};
}

/*
 * The given readMazeFile function correctly reads a well-formed
 * maze from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readMazeFile(string filename, Grid<bool>& maze) {
    /* The following code reads data from the file into a Vector
     * of strings representing the lines of the file.
     */
    ifstream in;

    if (!openFile(in, filename))
        error("Cannot open file named " + filename);

    Vector<string> lines = stringSplit(readEntire(in), '\n');

    /* Now that the file data has been read into the Vector, populate
     * the maze grid.
     */
    int numRows = lines.size();        // rows is count of lines
    int numCols = lines[0].length();   // cols is length of line
    maze.resize(numRows, numCols);     // resize grid dimensions

    for (int r = 0; r < numRows; r++) {
        if (lines[r].length() != numCols) {
            error("Maze row has inconsistent number of columns");
        }
        for (int c = 0; c < numCols; c++) {
            char ch = lines[r][c];
            if (ch == '@') {        // wall
                maze[r][c] = false;
            } else if (ch == '-') { // corridor
                maze[r][c] = true;
            } else {
                error("Maze location has invalid character: '" + charToString(ch) + "'");
            }
        }
    }
}

/* The given readSolutionFile correctly reads a path from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readSolutionFile(string filename, Vector<GridLocation>& soln) {
    ifstream in;

    if (!openFile(in, filename)) {
        error("Cannot open file named " + filename);
    }

    if (!(in >> soln)) {// if not successfully read
        error("Maze solution did not have the correct format.");
    }
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("generateValidMoves on location in the center of 3x3 grid with no walls") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation center = {1, 1};
    Set<GridLocation> expected = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};

    EXPECT_EQUAL(generateValidMoves(maze, center), expected);
}

PROVIDED_TEST("generateValidMoves on location on the side of 3x3 grid with no walls") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation side = {0, 1};
    Set<GridLocation> expected = {{0, 0}, {0, 2}, {1, 1}};

    EXPECT_EQUAL(generateValidMoves(maze, side), expected);
}

PROVIDED_TEST("generateValidMoves on corner of 2x2 grid with walls") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    GridLocation corner = {0, 0};
    Set<GridLocation> expected = {{1, 0}};

    EXPECT_EQUAL(generateValidMoves(maze, corner), expected);
}

PROVIDED_TEST("validatePath on correct solution, hand-constructed maze") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    Vector<GridLocation> soln = { {0 ,0}, {1, 0}, {1, 1} };

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on correct solution read from file, medium maze") {
    Grid<bool> maze;
    Vector<GridLocation> soln;
    readMazeFile("res/5x7.maze", maze);
    readSolutionFile("res/5x7.soln", soln);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on invalid path should raise error") {
    Grid<bool> maze = {{true, false},
                       {true, true},
                       {true, true}};
    Vector<GridLocation> notBeginAtEntry = { {1, 1}, {2, 1} };
    Vector<GridLocation> notEndAtExit = { {0, 0}, {1, 0}, {2, 0} };
    Vector<GridLocation> moveThroughWall = { {0 ,0}, {0, 1}, {1, 1}, {2, 1} };

    EXPECT_ERROR(validatePath(maze, notBeginAtEntry));
    EXPECT_ERROR(validatePath(maze, notEndAtExit));
    EXPECT_ERROR(validatePath(maze, moveThroughWall));
}

PROVIDED_TEST("solveMazeBFS on file 5x7") {
    Grid<bool> maze;
    readMazeFile("res/5x7.maze", maze);
    Vector<GridLocation> soln = solveMazeBFS(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("solveMazeDFS on file 21x23") {
    Grid<bool> maze;
    readMazeFile("res/21x23.maze", maze);
    Vector<GridLocation> soln = solveMazeDFS(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}


/* * * * * * Student Test Cases * * * * * */

// A maze with only one open cell.
// The entrance and exit are the same location.
STUDENT_TEST("solveMazeBFS on 1x1 maze") {
    Grid<bool> maze = {{true}};

    Vector<GridLocation> soln = solveMazeBFS(maze);

    Vector<GridLocation> expected = {{0, 0}};
    EXPECT_EQUAL(soln, expected);
}

// A maze with only one possible route to the exit.
STUDENT_TEST("solveMazeBFS on maze with only one possible path") {
    Grid<bool> maze = {
        {true,  false, false},
        {true,  true,  false},
        {false, true,  true}
    };

    Vector<GridLocation> soln = solveMazeBFS(maze);

    Vector<GridLocation> expected = {
        {0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}
    };

    EXPECT_EQUAL(soln, expected);
    EXPECT_NO_ERROR(validatePath(maze, soln));
}

// A maze with multiple possible routes to the exit.
// BFS should return a shortest path.
STUDENT_TEST("solveMazeBFS finds shortest path") {
    Grid<bool> maze = {
        {true, true,  true},
        {true, true,  true},
        {true, true,  true}
    };

    Vector<GridLocation> soln = solveMazeBFS(maze);

    // The shortest path from (0,0) to (2,2) requires 4 moves.
    EXPECT_EQUAL(soln.size(), 5);
    EXPECT_NO_ERROR(validatePath(maze, soln));
}

// A maze where the exit cannot be reached.
STUDENT_TEST("solveMazeBFS on maze with no solution") {
    Grid<bool> maze = {
        {true,  false},
        {false, true}
    };

    Vector<GridLocation> soln = solveMazeBFS(maze);

    EXPECT_EQUAL(soln.size(), 0);
}

// DFS should also find a valid path when one exists.
STUDENT_TEST("solveMazeDFS on maze with only one possible path") {
    Grid<bool> maze = {
        {true,  false, false},
        {true,  true,  false},
        {false, true,  true}
    };

    Vector<GridLocation> soln = solveMazeDFS(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

// DFS should return an empty path when the exit is unreachable.
STUDENT_TEST("solveMazeDFS on maze with no solution") {
    Grid<bool> maze = {
        {true,  false},
        {false, true}
    };

    Vector<GridLocation> soln = solveMazeDFS(maze);

    EXPECT_EQUAL(soln.size(), 0);
}

// A path that revisits a location should be rejected.
STUDENT_TEST("validatePath rejects repeated locations") {
    Grid<bool> maze = {
        {true, true},
        {true, true}
    };

    Vector<GridLocation> soln = {
        {0, 0}, {0, 1}, {1, 1}, {1, 0},
        {0, 0}, {1, 0}, {1, 1}
    };

    EXPECT_ERROR(validatePath(maze, soln));
}

// An empty path should be rejected.
STUDENT_TEST("validatePath rejects empty path") {
    Grid<bool> maze = {
        {true, true},
        {true, true}
    };

    Vector<GridLocation> soln;

    EXPECT_ERROR(validatePath(maze, soln));
}


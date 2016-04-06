#ifndef __MMAZEH__
#define __MMAZE_H__

#include <vector>
#include <queue>
#include <utility>
#include <iostream>

/*
    The maze has n x n cells, so a maximum of 
    n+1 walls can exist for any row or coloumn,
    including border walls.
    
    The start can be in any corner of the maze.
    We start at (0, 0) with an orientation of "North" 
    regardless of the viewer's relativity.
    The destination is the center 2 x 2 cells.
    We can only move to the cell we are facing.
    
    Let '#' denote a wall, and ' ' denote a cell.
    Path-planning will use the A* algorithm.
*/

typedef enum mouseOrientation {
    North, East, South, West
    } orientation;

class mMaze {
    private:
        vector<vector<char> > maze;
        unsigned cellX;
        unsigned cellY;
        orientation direction;
    public:
        mMaze();
        
        void printMaze();
        
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        
        void turnLeft();
        void turnRight();
        
        bool checkLeftWall();
        bool checkRightWall();
        bool checkFrontWall();
};

#endif

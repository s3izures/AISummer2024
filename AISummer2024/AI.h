#pragma once
#include <raylib.h>
#include <vector>
#include <string>
#include <float.h> // FOR FLT MAX
#include <stdio.h> // FOR FLT MAX
#include "Node.h"

using namespace std;

// Ai Class
class Ai
{
public:
#define ROWS 10
#define COLS 20
#define NODE_SIZE 50

    vector<vector<Node>> grid;
    Node pointA, pointB;

    void Main();
    void Start();
    void UpdateAndDraw();

    // SEARCH ALGORITHMS
    vector<Node*> bfsTracedPath;
    void BFS(Node* start, Node* goal);
    Color bfsColor = Color{ 200,0,0,100 };

    vector<Node*> dfsTracedPath;
    void DFS(Node* start, Node* goal);
    Color dfsColor = Color{ 200,0,0,100 };



    vector<Node*> GetNeighbours(Node* node)
    {
        vector<Node*> neighbours;

        auto isWithinGrid = [&](int row, int col) -> bool
            {
                return row >= 0 &&
                    col >= 0 &&
                    row < ROWS &&
                    col < COLS;
            };

        // check north
        if (isWithinGrid(node->row - 1, node->col))
        {
            neighbours.push_back(&grid[node->row - 1][node->col]);
        }

        //check south
        if (isWithinGrid(node->row + 1, node->col))
        {
            neighbours.push_back(&grid[node->row + 1][node->col]);
        }

        //check east
        if (isWithinGrid(node->row, node->col - 1))
        {
            neighbours.push_back(&grid[node->row][node->col - 1]);
        }

        //check west
        if (isWithinGrid(node->row, node->col + 1))
        {
            neighbours.push_back(&grid[node->row][node->col + 1]);
        }

        return neighbours;
    }
};
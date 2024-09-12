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
    int threshold = 2;
    int pathIndex = 0;
    bool trackBool = false;

    void Main();
    void Start();
    void UpdateAndDraw();

    Node* GetRandNode();
    Node* GetSpecialNode(NodeState node);

    // SEARCH ALGORITHMS



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
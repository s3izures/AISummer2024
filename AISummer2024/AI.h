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

    // SEARCH ALGORITHMS
    vector<Node*> bfsTracedPath;
    void BFS(Node* start, Node* goal);
    Color bfsColor = Color{ 0,0,255,100 };

    vector<Node*> dfsTracedPath;
    void DFS(Node* start, Node* goal);
    Color dfsColor = Color{ 255,0,0,100 };

    vector<Node*> djikstraTracedPath;
    void Djikstra(Node* start, Node* goal);
    Color djikstraColor = Color{ 0,255,0,100 };

    vector<Node*> aStarTracedPath;
    void AStar(Node* start, Node* goal);
    Color aStarColor = Color{ 255,0,255,100 };



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

    void CreateHotspot(Node* node, int size)
    {
        Node* current = node;
        grid[current->row][current->col].weight = size;

        auto isWithinGrid = [&](int row, int col) -> bool
            {
                return row >= 0 &&
                    col >= 0 &&
                    row < ROWS &&
                    col < COLS;
            };

        for (int i = size; i > 0; i--)
        {
            // check north
            if (isWithinGrid(current->row - i, current->col))
            {
                grid[current->row - i][current->col].weight += size - i;
            }

            //check south
            if (isWithinGrid(current->row + i, current->col))
            {
                grid[current->row + i][current->col].weight += size - i;
            }

            //check east
            if (isWithinGrid(current->row, current->col - i))
            {
                grid[current->row][current->col - i].weight += size - i;
            }

            //check west
            if (isWithinGrid(current->row, current->col + i))
            {
                grid[current->row][current->col + i].weight += size - i;
            }
        }
    }
};
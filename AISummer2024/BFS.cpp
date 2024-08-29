#include "AI.h"
#include <queue>

vector<Node*> Ai::GetNeighbours(Node* node)
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

void Ai::BFS(Node* start, Node* goal)
{
    bfsTracedPath.clear();

    // resetting the nodes in the grid
    for (auto& row : grid)
    {
        for (auto& node : row)
        {
            node.Reset();
        }
    }

    // openset is every node we still have to examine
    queue<Node*> openSet;

    openSet.push(start);    // We begin by pushing the start into it

    start->visited = true;

    while (!openSet.empty())
    {
        Node* current = openSet.front();    // get the first node of the queue
        openSet.pop();

        if (current->atSameSpot(*goal))
        {
            // we have reached the goal
            while (current != start)
            {
                bfsTracedPath.push_back(current);

                current = current->parent;
            }

            reverse(bfsTracedPath.begin(), bfsTracedPath.end());

            return;
        }

        // add the neighbours to the open set
        for (Node* neighbour : GetNeighbours(current))
        {
            if (neighbour->blocked || neighbour->visited)
            {
                continue;
            }

            neighbour->visited = true;
            neighbour->parent = current;

            neighbour->step = current->step + 1;

            openSet.push(neighbour);
        }
    }
}
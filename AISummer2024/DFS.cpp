#include "AI.h"
#include <stack>

void Ai::DFS(Node* start, Node* goal)
{
    dfsTracedPath.clear();

    // resetting the nodes in the grid
    for (auto& row : grid)
    {
        for (auto& node : row)
        {
            node.Reset();
        }
    }

    // openset is every node we still have to examine
    stack<Node*> openSet;
    openSet.push(start);
    start->visited;

    while (!openSet.empty())
    {
        Node* current = openSet.top();
        openSet.pop();

        if (current->atSameSpot(*goal))
        {
            // we have reached the goal
            while (current != start)
            {
                dfsTracedPath.push_back(current);

                current = current->parent;
            }
            reverse(dfsTracedPath.begin(), dfsTracedPath.end());
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
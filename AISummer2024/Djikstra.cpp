#include "AI.h"
#include <queue>

void Ai::Djikstra(Node* start, Node* goal)
{
    //hard reset
    djikstraTracedPath.clear();
    for (auto& row : grid)
    {
        for (auto& node : row)
        {
            node.Reset();
        }
    }

    auto Compare = [](Node* a, Node* b) { return a->gCost > b->gCost; };

    priority_queue<Node*, vector<Node*>, decltype(Compare)> openSet(Compare);

    //begin all nodes at infinity
    start->gCost = 0;
    start->step = 0;
    openSet.push(start);

    while (!openSet.empty())
    {
        Node* current = openSet.top();
        openSet.pop();

        if (current->atSameSpot(*goal))
        {
            // path reconstruction
            while (current != start)
            {
                djikstraTracedPath.push_back(current);
                current = current->parent;
            }

            reverse(djikstraTracedPath.begin(), djikstraTracedPath.end());
            return;
        }

        for (Node* neighbour : GetNeighbours(current))
        {
            if (neighbour->blocked || neighbour->visited)
            {
                continue;
            }

            //== Calculate tentative cost ==

            float tenCost = current->gCost + current->weight;

            //Neighbour's path is better
            if (tenCost < neighbour->gCost + neighbour->weight)
            {
                neighbour->gCost = tenCost;
                neighbour->parent = current;
                neighbour->visited = true;
                neighbour->step = current->step + 1;
                openSet.push(neighbour);
            }
            //==============================
        }
    }

}
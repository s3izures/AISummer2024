#include "AI.h"
#include <queue>
#include <unordered_map>

void Ai::AStar(Node* start, Node* goal)
{
    aStarTracedPath.clear();
    for (auto& row : grid)
    {
        for (auto& node : row)
        {
            node.Reset();
        }
    }

    auto Heuristic = [](Node* a, Node* b) -> float { 
        return abs(a->row - b->row) + abs(a->col - b->col); 
        };

    auto Compare = [](Node* a, Node* b) { 
        return a->fCost > b->fCost || (a->fCost == b->fCost && a->hCost > b->hCost);
        };

    priority_queue<Node*, vector<Node*>, decltype(Compare)> openSet(Compare);
    //When typed 'top' find the one that meets the condition

    unordered_map<Node*, float> gScore;
    //Map of cheapest route from start to each node

    for (auto& row : grid)
    {
        for (auto& node : row)
        {
            gScore[&node] = INFINITY;
        }
    }

    gScore[start] = 0;
    start->hCost = Heuristic(start, goal);
    start->gCost = 0;
    start->step = 0;
    start->visited = true;
    openSet.push(start);

    while (!openSet.empty())
    {
        Node* current = openSet.top();
        openSet.pop();

        if (current->atSameSpot(*goal))
        {
            // path reconstruction
            while (current != nullptr)
            {
                aStarTracedPath.push_back(current);
                current = current->parent;
            }
            reverse(aStarTracedPath.begin(), aStarTracedPath.end());
            return;
        }

        for (Node* neighbour : GetNeighbours(current))
        {
            if (neighbour->blocked || neighbour->visited)
            {
                continue;
            }

            float tenCost = gScore[current] + current->weight;

            if (tenCost < gScore[neighbour] + neighbour->weight)
            {
                neighbour->parent = current;
                gScore[neighbour] = tenCost;
                neighbour->hCost = Heuristic(neighbour, goal);
                neighbour->fCost = gScore[neighbour] + neighbour->hCost;
                neighbour->step = current->step + 1;
                neighbour->visited = true;
                openSet.push(neighbour);
            }
        }
    }
}
#include "Ai.h"
#include <vector>
#include <iostream>

using namespace std;

void Ai::Main()
{
    InitWindow(1000, 500, "AI - Pathfinding");

    Start();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        UpdateAndDraw();

        EndDrawing();
    }

    CloseWindow();
}

void Ai::Start()
{
    // re-create the nodes
    grid.clear();
    for (int row = 0; row < ROWS; row++)
    {
        float y = NODE_SIZE * row;
        vector<Node> rowNodes;
        for (int col = 0; col < COLS; col++)
        {
            float x = NODE_SIZE * col;
            Node node = { row, col, Vector2{x, y} };
            node.SetState(NodeState::Idle);
            rowNodes.push_back(node);
        }
        grid.push_back(rowNodes);
    }

    // take some (e.g., 5, 10, or 20) from sqaures randomly and put in blockd ones
    for (int i = 0; i < 25; i++)
    {
        GetRandNode()->SetState(NodeState::Blocked);
    }

    GetRandNode()->SetState(NodeState::Start, 0);
    GetRandNode()->SetState(NodeState::Goal);
}

void Ai::UpdateAndDraw()
{

    for (int i = 0; i < (int)(grid.size()); i++)
    {
        for (int j = 0; j < (int)(grid[i].size()); j++)
        {
            grid[i][j].Draw();
        }
    }



    // Check if the "R" key is pressed
    if (IsKeyPressed(KEY_R)) 
    { 
        pathIndex = 0;
        Start(); 
    } // RESTART

    if (IsKeyPressed(KEY_B))
    {
        if (GetSpecialNode(NodeState::Goal)->isTransitioning) return;

        GetSpecialNode(NodeState::Goal)->SetState(NodeState::Idle, 99, true);
        GetRandNode()->SetState(NodeState::Goal, 0, true);
    }

    if (IsKeyPressed(KEY_L)) 
    { 
        trackBool = true; 
    };
}

Node* Ai::GetRandNode()
{
    int randRow;
    int randCol;

    do
    {
        randRow = GetRandomValue(0, (int)(grid.size()) - 1);
        randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    } while (grid[randRow][randCol].currentState == NodeState::Blocked || grid[randRow][randCol].currentState == NodeState::Start || grid[randRow][randCol].currentState == NodeState::Goal);

    return &grid[randRow][randCol];
}

Node* Ai::GetSpecialNode(NodeState state)
{
    for (int i = 0; i < (int)(grid.size()); i++)
    {
        for (int j = 0; j < (int)(grid[i].size()); j++)
        {
            if (grid[i][j].currentState == state)
            {
                return &grid[i][j];
            }
        }
    }

    return &grid[0][0]; // not found
}

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
            Node node = { row, col, Vector2{x, y}, DARKGRAY, LIGHTGRAY }; // fill, stroke
            rowNodes.push_back(node);
        }
        grid.push_back(rowNodes);
    }

    // take some (e.g., 5, 10, or 20) from sqaures randomly and put in blockd ones
    for (int i = 0; i < 50; i++)
    {
        int randRow = GetRandomValue(0, (int)(grid.size()) - 1);
        int randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
        grid[randRow][randCol].blocked = true;
    }


    // choose a random home and dest from squares
    int randRow = GetRandomValue(0, (int)(grid.size()) - 1);
    int randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    while (grid[randRow][randCol].blocked && randRow != pointB.row && randCol != pointB.col)
    {
        randRow = GetRandomValue(0, (int)(grid.size()) - 1);
        randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    }
    pointA = grid[randRow][randCol];
    pointA.costText = "A";
    pointA.fillColor = GREEN;
    pointA.blocked = true; // this just so the color renders

    randRow = GetRandomValue(0, (int)(grid.size()) - 1);
    randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    while (grid[randRow][randCol].blocked && randRow != pointA.row && randCol != pointA.col)
    {
        randRow = GetRandomValue(0, (int)(grid.size()) - 1);
        randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    }
    pointB = grid[randRow][randCol];
    pointB.costText = "B";
    pointB.fillColor = BLUE;
    pointB.blocked = true; // this just so the color renders


    randRow = GetRandomValue(0, (int)(grid.size()) - 1);
    randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    while (grid[randRow][randCol].blocked && randRow != pointA.row && randCol != pointA.col)
    {
        randRow = GetRandomValue(0, (int)(grid.size()) - 1);
        randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    }
    int randSize = GetRandomValue(threshold + 1, 5);
    //CreateHotspot(&grid[randRow][randCol], randSize);
}

void Ai::UpdateAndDraw()
{
    for (int i = 0; i < (int)(grid.size()); i++)
    {
        for (int j = 0; j < (int)(grid[i].size()); j++)
        {
            grid[i][j].Draw();
            /*if (grid[i][j].weight > 0)
            {
                unsigned char alpha = 50 + grid[i][j].weight * 20;
                grid[i][j].DrawPath(Color{ 255,255,0,alpha });
            }*/
        }
    }

    // Check if the "R" key is pressed
    if (IsKeyPressed(KEY_R)) { Start(); } // RESTART

    /*
    for (Node* node : bfsTracedPath)
    {
        node->DrawPath(bfsColor);
    }

    for (Node* node : dfsTracedPath)
    {
        node->DrawPath(dfsColor);
    }
    */

    for (Node* node : djikstraTracedPath)
    {
        node->DrawPath(djikstraColor);
    }

    // draw home and dest. Reset 
    pointA.step = -1; pointA.Draw();
    pointB.step = -1; pointB.Draw();

    //BFS(&pointA, &pointB);
    //DFS(&pointA, &pointB);
    Djikstra(&pointA, &pointB);
}
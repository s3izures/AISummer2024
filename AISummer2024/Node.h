#pragma once
#include <raylib.h>
#include <vector>
#include <string>
#include <float.h> // FOR FLT MAX
#include <stdio.h> // FOR FLT MAX

enum NodeState
{
    Idle,
    Exploring,
    Blocked,
    Visited,
    Goal,
    Start
};

using namespace std;

// Standalone Node Struct
struct Node
{
    int row, col;
    Vector2 position;
    Color fillColor = RAYWHITE;
    Color outlineColor = LIGHTGRAY;
    int weight = 1;
    NodeState currentState = Idle;

    string costText = "";

    // Constructor for convenience
    Node(int row = 0, int col = 0, Vector2 position = {})
    {
        this->row = row;
        this->col = col;
        this->position = position;
    }

    Color GetStateColor(NodeState state)
    {
        switch (state)
        {
        default:
        case Idle:      return RAYWHITE;
        case Start:     return DARKBLUE;
        case Goal:      return BLUE;
        case Visited:   return ORANGE;
        case Exploring: return YELLOW;
        case Blocked:   return DARKGRAY;
        }
    }

    float transitionTime = 0.0f;
    bool isTransitioning = false;
    NodeState nextState;
    Color targetColor;
    void SetState(NodeState state, float gCost = FLT_MAX, bool transit = false)
    {
        if (transit)
        {
            isTransitioning = true;
            transitionTime = 0.0f;
            nextState = state;
            targetColor = GetStateColor(state);
        }
        else
        {
            currentState = state;
            costText = "";
            this->gCost = gCost;
            fillColor = GetStateColor(currentState);
        }
    }

    Color LerpColor(float t)
    {
        return Color{   (unsigned char)(fillColor.r + (targetColor.r - fillColor.r) * t) ,
                        (unsigned char)(fillColor.g + (targetColor.g - fillColor.g) * t) ,
                        (unsigned char)(fillColor.b + (targetColor.b - fillColor.b) * t) ,
                        (unsigned char)(fillColor.a + (targetColor.a - fillColor.a) * t) };
    }

    // Draw the node on the screen
    void Draw()
    {
        if (isTransitioning)
        {
            transitionTime += GetFrameTime();
            if (transitionTime < 2.0f)
            {
                DrawRectangleV(position, Vector2{ 50, 50 }, LerpColor(transitionTime / 2));
                DrawRectangleLines(position.x, position.y, 50, 50, outlineColor);

            }
            else
            {
                isTransitioning = false;
                SetState(nextState);
            }
        }
        else
        {
            DrawRectangleV(position, Vector2{ 50, 50 }, fillColor);
            DrawRectangleLines(position.x, position.y, 50, 50, outlineColor);
        }



        // Draw Number
        if (gCost < 100000)
        {
            costText = to_string(static_cast<int>(gCost));
        }


        // Measure the text size to center it
        int textWidth = MeasureText(costText.c_str(), 20);
        int textHeight = 20;  // Font size is 20

        // Calculate the center position for the text
        Vector2 textPosition = { position.x + 25 - textWidth / 2, position.y + 25 - textHeight / 2 };

        // Draw the text in the center of the rectangle
        DrawText(costText.c_str(), textPosition.x, textPosition.y, 20, BLACK);
    }



    void DrawPath(Color color)
    {
        DrawRectangleV(position, Vector2{ 50, 50 }, color);
    }

    // A* related costs
    float gCost = FLT_MAX; // ground cost from the start node to the current node,
    float hCost = FLT_MAX; // heuristic estimated cost from the current node to the end node
    float fCost = FLT_MAX; // final total cost (gCost + hCost)

    Node* parent = nullptr;
    bool visited = false; // Add this flag to your Node structure

    void Reset()
    {
        parent = nullptr;
        visited = false;

        gCost = FLT_MAX; // ground cost from the start node to the current node,
        hCost = FLT_MAX; // heuristic estimated cost from the current node to the end node
        fCost = FLT_MAX; // final total cost (gCost + hCost)
    }


    // New member function to check if this node is at the same position as another node
    bool atSameSpot(const Node& other) const
    {
        return this->row == other.row && this->col == other.col;
    }

};

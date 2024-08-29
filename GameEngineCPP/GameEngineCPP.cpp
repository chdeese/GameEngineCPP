#include "raylib.h"
#include <iostream>
#include "Engine/List.h"

int main(void)
{

    GameEngine::List<int> list = GameEngine::List<int>();

    for (auto iter = list.begin(); iter != list.end(); iter++)
    {

    }



    InitWindow(800, 450, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}


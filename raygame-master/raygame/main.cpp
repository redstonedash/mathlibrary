/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "UTILS.h"
#include "raylib.h"
#include <iostream>
#include "PlayerMovement.h"
#include <fstream>
#include <string> 
#include "GameObject.h"
#include <vector>


int MAX_GAME_OBJECTS = 20;

std::vector<GameObject> objectPool;

Player player = Player();

int main()
{
	objectPool = std::vector<GameObject>();
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1060;
	int screenHeight = 640;
	int lightCount = 2;
	double time = 0;

	SetConfigFlags(FLAG_VSYNC_HINT);

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	/*std::ifstream in("resources/shaders/glsl330/test.fs");
	std::string contents((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	std::cout << contents.c_str() << "\n\n";
	contents.replace(contents.find("@n"),2,std::to_string(lightCount));
	contents.replace(contents.find("@n"), 2, std::to_string(lightCount));

	std::cout << contents.c_str();*/

	SetTargetFPS(120);
	//--------------------------------------------------------------------------------------

	// Main game loop
	Vector2 mouseDelta = { 0,0 };
	Vector2 mousePos = { 0,0 };

	for (int i = 0; i < MAX_GAME_OBJECTS; i++) {
		objectPool.push_back(GameObject());
	}

	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		time += GetFrameTime();
		// Update
		//----------------------------------------------------------------------------------

		BeginDrawing();

		ClearBackground(WHITE);

		for (float i = 0; i < 1000; i++) {
			DrawPixel(i, (float)i / 10.0f, RED);
			DrawPixel(i, (float)math::sin((float)i / 1000.0f * 6.28) * 200 + 320, BLACK);
		}
		std::cout << std::to_string((float)math::sin((float)GetTime() / 100.0f * 6.28)) << "\n";
		math::vec2 a = math::vec2(2, 1).getNormalized();
		DrawLine(0, 0, a.x*100, a.y * 100, BLUE);

		DrawFPS(0, 0);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	for (int i = 0; i < MAX_GAME_OBJECTS; i++) {
		if (objectPool.at(i).enabled)
			objectPool.at(i).unload();
	}

	objectPool.clear();

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
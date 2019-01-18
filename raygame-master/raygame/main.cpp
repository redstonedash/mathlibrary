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
#include <fstream>
#include <string> 
#include "GameObject.h"
#include <vector>

int playerBeingGrabed = 1; //player 1, no one, player 2

struct Node {
	int playerNumber;
	math::mat3 transform;
	math::vec2 translation;
	float rotation; //TODO: rework rotation
	math::vec2 scale;
	Node* child;
	Color c;
	/*
	[Xx][Yx][Tx]
	[Xy][Yy][Ty]
	[ 0][ 0][ 1]
	*/
};


void Draw(Node n, Node* Offset) {
	float scaleOffset = 50; // makes lines long enough to be visable without effecting scale
	n.transform = math::mat3::translation(n.translation) * math::mat3::rotation(n.rotation) * math::mat3::scale(n.scale);
	if (!Offset) {
		Offset = &n;
	} else {
		Offset->transform = Offset->transform * n.transform;
	}
	DrawLine(Offset->transform.mm[0][2], Offset->transform.mm[1][2], Offset->transform.mm[0][2] + Offset->transform.mm[0][0]*scaleOffset, Offset->transform.mm[1][2] + Offset->transform.mm[1][0]*scaleOffset, RED);
	DrawLine(Offset->transform.mm[0][2], Offset->transform.mm[1][2], Offset->transform.mm[0][2] + Offset->transform.mm[0][1]*scaleOffset, Offset->transform.mm[1][2] + Offset->transform.mm[1][1]*scaleOffset, BLUE);
	if (n.child) {
		Draw(*n.child, Offset);
	}
}


int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1060;
	int screenHeight = 640;

	Node node = Node();
	node.transform = math::mat3(1, 0, 0,
								0, 1, 0,
								0, 0, 1);
	node.translation = math::vec2(screenWidth/2, screenHeight/2);
	node.rotation = 0;
	node.scale = math::vec2(1,1);
	node.c = BLACK;
	Node child = Node();
	child.transform = math::mat3(1, 0, 0,
	      0, 1, 0,
	      0, 0, 1);
	child.translation = math::vec2(50, 100);
	child.rotation = 0;
	child.scale = math::vec2(1, 1);
	child.c = BLACK;
	node.child = &child;

	Node spinner = Node();
	spinner.transform = math::mat3(1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	spinner.translation = math::vec2(50, 100);
	spinner.rotation = 0;
	spinner.scale = math::vec2(1, 1);
	spinner.c = BLACK;
	child.child = &spinner;

	SetConfigFlags(FLAG_VSYNC_HINT);

	InitWindow(screenWidth, screenHeight, "GRABTHROW");

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
	bool OddFrame = true;
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------

		BeginDrawing();

		ClearBackground(WHITE);
		//node.rotation += GetFrameTime();
		if (GetKeyPressed() >= 0) {
			std::cout << GetKeyPressed() << "\n";
			switch (GetKeyPressed())
			{
			case 113:
				node.rotation += math::Tau / 16;
				break;
			case 119:
				node.rotation -= math::Tau / 16;
				break;
			case 101:
				node.scale.x += 1;
				break;
			case 114:
				node.scale.x -= 1;
				break;
			case 116:
				node.scale.y += 1;
				break;
			case 121:
				node.scale.y -= 1;
				break;
			case 117:
				node.translation.x += 5;
				break;
			case 105:
				node.translation.x -= 5;
				break;
			case 111:
				node.translation.y += 5;
				break;
			case 112:
				node.translation.y -= 5;
				break;
			default:
				break;
			}
			switch (GetKeyPressed())
			{
			case 97:
				child.rotation += math::Tau / 16;
				break;
			case 115:
				child.rotation -= math::Tau / 16;
				break;
			case 100:
				child.scale.x += 1;
				break;
			case 102:
				child.scale.x -= 1;
				break;
			case 103:
				child.scale.y += 1;
				break;
			case 104:
				child.scale.y -= 1;
				break;
			case 106:
				child.translation.x += 5;
				break;
			case 107:
				child.translation.x -= 5;
				break;
			case 108:
				child.translation.y += 5;
				break;
			case 59:
				child.translation.y -= 5;
				break;
			default:
				break;
			}
		}
		spinner.rotation += GetFrameTime();
		Draw(node, nullptr);
		DrawFPS(0, 0);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
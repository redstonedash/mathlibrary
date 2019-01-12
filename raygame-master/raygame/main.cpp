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

struct Player {
	int playerNumber;
	math::mat3 transform;
	math::mat3 translation;
	math::mat3 rotation;
	math::mat3 scale;
	math::mat3 grabOffset;
	/*
	[Xx][Yx][Tx]
	[Xy][Yy][Ty]
	[ 0][ 0][ 1]
	*/
	math::vec2 velocity = { 0, 0};
	math::vec2 gamePadLastPos = { 0, 0 };
	float hitstun = 0;
	float stun = 0;
	//float invincibility; //if i have time
	float damage = 0;
	float lag = 0;
	Player(){}
	Player(int playerNumber) {
		this->playerNumber = playerNumber;
	}
};


Player playerArr[2];
void Draw(Player p) {
	Rectangle rect = Rectangle();
	rect.x = 0;
	rect.y = 0;
	rect.width  = 100;
	rect.height = 100;
	DrawRectanglePro(rect, { -p.transform.m3, -p.transform.m6 }, math::vec2(p.rotation.m1, p.rotation.m4).angleBetween({ 0,1 })*math::RAD_TO_DEG , 
		{ (unsigned char)(155 + 155 + (100 * p.playerNumber)),(unsigned char)(100 * p.playerNumber),(unsigned char)(155 + (100 * p.playerNumber)),(unsigned char)255 });
	//DrawRectanglePro(rect, { 500,500 }, i, PURPLE);
}

void Update(Player *p) {
	p->transform.m3 += p->velocity.x;
	p->transform.m6 += p->velocity.y;
	p->velocity.y += GetFrameTime()*10;
	/*PLAYER INPUT*/
	/*BEING GRABED*/
	/*DISABLED*/
	bool disabled = false;
	if (p->lag>0) {
		p->lag -= GetFrameTime();
		disabled = true;
	}
	if (true) {
		p->stun -= GetFrameTime();
		std::cout << GetFrameTime() << "\n";
		p->rotation *= math::mat3::rotation(GetFrameTime()); //TODO: delete this
		disabled = true;
	}
	if (p->hitstun > 0) {
		p->hitstun -= GetFrameTime();
		disabled = true;
	}
	if (disabled) goto applyTransformBeforeFunctionExit; //forgive me for i have sinned
	if (IsGamepadAvailable(p->playerNumber))
	{
		
		/*DODGE/GRAB*/
		if ((math::vec2(GetGamepadAxisMovement(p->playerNumber, 0),
			GetGamepadAxisMovement(p->playerNumber, 1)) - p->gamePadLastPos).magnitude() > 0.9 && math::vec2(GetGamepadAxisMovement(p->playerNumber, 0),
				GetGamepadAxisMovement(p->playerNumber, 1)).magnitude()>0.5) {
			//p->lag
		}
		/*THROW*/

		/*MOVEMENT*/
		p->velocity.x += GetGamepadAxisMovement(p->playerNumber, 0)*GetFrameTime()*30;
		if (GetGamepadAxisMovement(p->playerNumber, 1)*GetFrameTime() > 0 && p->velocity.y) {
			p->velocity.y += GetGamepadAxisMovement(p->playerNumber, 1) * GetFrameTime() * 40;
		}
		p->gamePadLastPos = {
			GetGamepadAxisMovement(p->playerNumber, 0),
			GetGamepadAxisMovement(p->playerNumber, 1)
		};
	}
	applyTransformBeforeFunctionExit: //NEVER CALL RETURN IN THIS FUNCTION! ALWAYS GO HERE INSTEAD!
	p->transform = p->scale*p->rotation*p->translation;
	return;
}

int main()
{
	playerArr[0] = Player(GAMEPAD_PLAYER1);
	playerArr[1] = Player(GAMEPAD_PLAYER2);
	playerArr[0].transform = math::mat3(0, 0, 0, 
										0, 0, 0,
										0, 0, 1);
	playerArr[1].transform = math::mat3(0, 0, 0,
										0, 0, 0,
										0, 0, 1);
	playerArr[0].translation = math::mat3::translation(200, 200);
	playerArr[1].translation = math::mat3::translation(800, 100);
	playerArr[0].rotation = math::mat3::identity();
	playerArr[1].rotation = math::mat3::identity();
	playerArr[0].scale = math::mat3::scale(1,1);
	playerArr[1].scale = math::mat3::scale(-1,1);

	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1060;
	int screenHeight = 640;

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
		if (OddFrame) {
			Update(&playerArr[0]);
			Update(&playerArr[1]);
		} else {
			Update(&playerArr[1]);
			Update(&playerArr[0]);
		}
		Draw(playerArr[0]);
		Draw(playerArr[1]);
		DrawFPS(0, 0);

		EndDrawing();
		//----------------------------------------------------------------------------------
		OddFrame = !OddFrame;
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
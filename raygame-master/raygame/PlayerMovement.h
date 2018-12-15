#pragma once
#include "raylib.h"
#include <vector>
#include "GameObject.h"

struct Player { //Player is handled diferently than every other object in the game
	Camera camera = { 0 };
	Vector3 velocity = { 0,0,0 };
	Vector2 direction = { 105,0 };
	Vector3 spawnPoint;
	bool finished = false;
	bool Grounded = false;
	Player() {
		camera.position = { 0.0f, 0.0f, 0.0f };
		camera.target = { 0.0f, 0.0f, 0.0f };
		camera.up = { 0.0f, 1.0f, 0.0f };
		camera.fovy = 90.0f;
		camera.type = CAMERA_PERSPECTIVE;
	}
};

void sourceAccelerate(Player *p, Vector3 wishdir, float wishspeed, float accel);
void updatePlayer(Player* p, Vector2 mouseDelta, std::vector<GameObject> collisionArray);
void acceleratePlayer(Player* p, Vector3 wishdir);
bool playerDetectColision(Player* p, GameObject *m);
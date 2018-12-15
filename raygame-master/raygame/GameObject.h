#pragma once
#include "raylib.h"
#pragma warning(disable:4996)
struct GameObject {
	Model mesh;
	int cameraLoc;
	bool enabled = false;
	bool goal = false;
	float cameraPosition[3] = { 0,0,0 };
	GameObject() {

	}
	void enablePlatform(const char* model) {
		mesh = LoadModel(model);
		mesh.material.shader = LoadShader("resources/shaders/glsl330/base.vs",
			"resources/shaders/glsl330/test.fs");
		enabled = true;
		cameraLoc = GetShaderLocation(mesh.material.shader, "cameraPos");
	}
	void draw(Camera c) {
		cameraPosition[0] = c.position.x;
		cameraPosition[1] = c.position.y;
		cameraPosition[2] = c.position.z;
		SetShaderValue(mesh.material.shader, cameraLoc, cameraPosition, 3);
		DrawModel(mesh, {0,0,0}, 1, WHITE);

	}

	void unload() {
		UnloadModel(mesh);
		enabled = false;
		goal = false;
	}

	void disable() {
		enabled = false;
		goal = false;
	}
};

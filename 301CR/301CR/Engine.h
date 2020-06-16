#pragma once

#include "GLFW/glfw3.h"
#pragma comment(lib, "opengl32.lib")
#include <iostream>
using namespace std;

class Engine
{
public:
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static float getDT();

	Engine();
	~Engine();

	void Update();
	void BeginRender();
	void EndRender();

	bool Initialize(const char* windowTitle);
private:
	static GLFWwindow* window;

	static float dt; //delta time
	float lastTime;
};


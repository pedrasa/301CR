#pragma once

#include "GLFW/glfw3.h"
class Keyboard
{
public:
	static void KeyCallBack(GLFWwindow* window, int key, int scancode,int action, int mods);

	static bool keyDown(int key);
	static bool keyUp(int key);
	static bool key(int key);
private:
	static bool keys[];
	static bool keysDown[];
	static bool keysUp[];
};


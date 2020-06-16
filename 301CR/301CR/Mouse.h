#pragma once

#include "GLFW/glfw3.h"
class Mouse
{
public:
	static void MousePosCallBack(GLFWwindow* window,double _mouseX,double _mouseY);
	static void MouseButtonCallBack(GLFWwindow* window, int button,int action,int mods);

	static double getMouseX();
	static double getMouseY();

	static bool buttonDown(int button);
	static bool buttonUp(int button);
	static bool buttonPress(int button);
private:
	static double mouseX;
	static double mouseY;

	static bool mouseButtons[];
	static bool mouseButtonsDown[];
	static bool mouseButtonsUp[];

};


#include "Mouse.h"
double Mouse::mouseX = 0;
double Mouse::mouseY = 0;
//exact same as keyboard but with the mouse buttons instead, we call mouse button last so we dont hvae to manually put in all the mouse buttons.
bool Mouse::mouseButtons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::mouseButtonsDown[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::mouseButtonsUp[GLFW_MOUSE_BUTTON_LAST] = { 0 };

void Mouse::MousePosCallBack(GLFWwindow* window, double _mouseX, double _mouseY)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	mouseX = _mouseX;
	mouseY = height - _mouseY;
}

void Mouse::MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
	if (button < 0)
		return;

	if (action != GLFW_RELEASE && mouseButtons[button] == false)
	{
		mouseButtonsDown[button] = true;
		mouseButtonsUp[button] = false;
	}

	if (action == GLFW_RELEASE && mouseButtons[button] == true)
	{
		mouseButtonsDown[button] = false;
		mouseButtonsUp[button] = true;
	}

	mouseButtons[button] = action != GLFW_RELEASE;
}

double Mouse::getMouseX()
{
	return mouseX;
}

double Mouse::getMouseY()
{
	return mouseY;
}

bool Mouse::buttonDown(int button)
{
	bool x = mouseButtonsDown[button];
	mouseButtonsDown[button] = false;
	return x;
}

bool Mouse::buttonUp(int button)
{
	bool x = mouseButtonsUp[button];
	mouseButtonsUp[button] = false;
	return x;
}

bool Mouse::buttonPress(int button)
{
	return mouseButtons[button];
}

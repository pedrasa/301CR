#include "Keyboard.h"
//the way we hand keyboard inputs, call backs lets us see what keys was called and then puts it in three categories, key down pressed, key pressed and then released and if the key is cosntantly pressed
bool Keyboard::keys[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysDown[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysUp[GLFW_KEY_LAST] = { 0 };

void Keyboard::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)//key is the key pressed and action is if it is pressed or not
{
	if (key < 0)
		return;
	if (action != GLFW_RELEASE && keys[key] == false)
	{
		keysDown[key] = true;
		keysUp[key] = false;
	}
	if (action != GLFW_RELEASE && keys[key] == true)
	{
		keysDown[key] = false;
		keysUp[key] = true;
	}

	keys[key] = action != GLFW_RELEASE;
}

bool Keyboard::keyDown(int key)
{
	bool x = keysDown[key];
	keysDown[key] = false;
	return x;
}

bool Keyboard::keyUp(int key)
{
	bool x = keysUp[key];
	keysUp[key] = false;
	return x;
}

bool Keyboard::key(int key)
{
	return keys[key];
}

#include "InputManager.h"
//the input manager handles the inputs we give it, tehre used to be more but this might also be used for chaging textures by the player
InputManager::InputManager(Flapper* _player)
{
	player = _player;
}

void InputManager::Update()
{
	if (Keyboard::key(GLFW_KEY_SPACE) || Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		player->Flap();
	}
}

#pragma once

#include "Mouse.h"
#include "Keyboard.h"
#include "Engine.h"
#include "Flapper.h"
#include "Pipe.h"
#include "serverManager.h"
class InputManager
{
public:
	InputManager(Flapper* _player);

	void Update();
private:
	Flapper* player;
	serverManager* mserverManager;
};


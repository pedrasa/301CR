#pragma once

#include "Sprite.h"
#include "RigidBody.h"
class Flapper
{
public:
	Flapper();
	Flapper(Sprite _sprite);

	void Update();
	void Render();

	void Flap();

	Sprite& getSprite();
	RigidBody& getRB();

	void Reset();
private:
	Sprite sprite;
	RigidBody rb;
	void HandleInput();
	float flapForce;
	float maxRot;
	float minRot;
};


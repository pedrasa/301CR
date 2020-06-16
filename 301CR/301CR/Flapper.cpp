#include "Flapper.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Engine.h"

Flapper::Flapper() //this is our flapper object that calls both the sprite and texture, and the physics and rigidbody for itself
{
	flapForce = 400;
	maxRot = 35;
	minRot = -maxRot;
}

Flapper::Flapper(Sprite _sprite) : Flapper()
{
	sprite = _sprite;
	Rect boundingRect = Rect();
	Vector3 sizeOffset(0.8, 0.3, 1);
	boundingRect.SetSize(*sprite.getSize() * *sprite.getScale() * sizeOffset);
	rb.Initialize(0.8f,-10,sprite.getPos(),sprite.getRot(),sprite.getScale(),sprite.getSize(), boundingRect);//creating the rigidbody
}

void Flapper::Update()
{

	HandleInput();

	sprite.Update();
	rb.Update();//this function makes it so we can actually move the flapper andthe sprite and rigidbody comes with

	float yVel = rb.getVel().y;
	if (flapForce == 0)
	{
		cout << "Error! Flapping will do you no good! Setting to 400" << endl;
		flapForce = 400;
	}
	float newRot = (maxRot / flapForce) * yVel;
	sprite.RotateTo(newRot);
}

void Flapper::Render()//calls rendering methods
{
	sprite.Render();
	rb.Render(Vector3(0, 0, 0));
}

void Flapper::Flap()
{
	rb.SetVel(Vector3(0, flapForce, 0));
	sprite.RotateTo(maxRot);
}

Sprite& Flapper::getSprite()
{
	return sprite;
}

RigidBody& Flapper::getRB()
{
	return rb;
}

void Flapper::Reset()
{
	sprite.MoveTo(Vector3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	sprite.RotateTo(0);
	rb.SetVel(Vector3(0, 0, 0));
}

// Private

void Flapper::HandleInput()
{
	if (Keyboard::keyDown(GLFW_KEY_SPACE) || Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		Flap();
	}
}

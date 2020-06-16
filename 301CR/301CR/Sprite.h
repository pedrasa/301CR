#pragma once

#include "GLFW/glfw3.h"
#include "Texture.h"
#include "Engine.h"
#include "Vector3.h"

#include <iostream>
#include <string>

using namespace std;
class Sprite
{
public:
	Sprite();
	Sprite(string imagePath);
	Sprite(string imagePath,Vector3 _Pos);

	void Update();
	void Render();

	void SpeedTo(float x);
	void SpeedBy(float x);

	void MoveTo(Vector3 vector);
	void MoveBy(Vector3 vector);

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void RotateTo(float x);
	void RotateBy(float x);

	void SetScale(float x);
	void SetScale(Vector3 vector);

	void FlipHorizontal();
	void FlipVertical();


	Vector3* getPos();
	float* getRot();
	Vector3* getScale();
	Vector3* getSize();

private:
	Texture texture;

	float speed;

	Vector3 pos;
	float rot;
	Vector3 scale;
	Vector3 size;
};


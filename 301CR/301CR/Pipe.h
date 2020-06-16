#pragma once

#include "Sprite.h"
#include "Rigidbody.h"
#include "Vector3.h"
class Pipe
{
public:
	static Sprite* pipeSprite;
	static void Initialize();

	Pipe();
	Pipe(Vector3 _pos);

	void SetGap(float _gap);//gap inbetween the pipes
	float GetPrevPos();//previous pos of the pipe

	void Update();
	void Render();

	void MoveTo(Vector3 to);
	void MoveBy(Vector3 by);

	float GetX();
	float GetWidth();

	RigidBody GetTopRB();//rigidbody for the top  and bottom pipe
	RigidBody GetBotRB();

private:
	void UpdatePos();

	Sprite topSprite;
	Sprite botSprite;
	RigidBody topRB;
	RigidBody botRB;

	Vector3 pos;
	float prevPos;

	float gap;
	float speed;//speed at which it moves to the left
};


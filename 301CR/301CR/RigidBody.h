#pragma once

#include "Vector3.h"
#include "Rect.h"
class RigidBody
{
public:
	RigidBody();

	static bool IsColliding(const RigidBody& rbA, const RigidBody& rbB);
	void Initialize(float _friction, float _gravity, Vector3* _pos, float* _rot, Vector3* _scale, Vector3* _size, Rect _boundingRect);

	void Update();
	void Render(Vector3 c);

	void AddForce(Vector3 f);

	Vector3 getVel();
	void SetVel(Vector3 _v);

private:
	Vector3* pos;
	float* rot;
	float lastRot;
	Vector3* scale;
	Vector3* size;

	float gravity;
	float friction;
	Vector3 vel;

	Rect boundingRect;
};


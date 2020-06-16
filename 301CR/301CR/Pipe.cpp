#include "Pipe.h"

#include "Pipe.h"
#include "Rect.h"
#include "Math.h"
#include "Engine.h"

Sprite* Pipe::pipeSprite = NULL;

void Pipe::Initialize()
{
	pipeSprite = new Sprite("Textures/pipe.png");
	pipeSprite->SetScale(Vector3(0.1f, 0.35f, 1));
}

Pipe::Pipe()
{
	if (!pipeSprite)
	{
		cout << "Trying to instantiate a Pipe without having called the Initialize method!" << endl;
		return;
	}
	//makes sure there is a pipe to create
	topSprite = Sprite(*pipeSprite);
	botSprite = Sprite(*pipeSprite);

	gap = 350;
	speed = 200;
}

Pipe::Pipe(Vector3 _pos) : Pipe() //where the pipe object is
{
	if (!pipeSprite)//if no pipe sprite just returns
	{
		return;
	}

	//sets position and previous position, _pipe used by the pipeManager
	pos = _pos + Vector3(GetWidth(), 0, 0);
	prevPos = pos.x;

	//update the position and flip the pipe on top so its sprite is hanging down
	UpdatePos();
	topSprite.FlipVertical();

	//then creates the top and bottoms bouding boxes and rigidbodies
	Rect topRC = Rect();
	topRC.SetSize(Vector3(Math::Abs(topSprite.getSize()->x * topSprite.getScale()->x), Math::Abs(topSprite.getSize()->y * topSprite.getScale()->y), 1));
	topRB = RigidBody();
	topRB.Initialize(1, 0, topSprite.getPos(), topSprite.getRot(), topSprite.getScale(), topSprite.getSize(), topRC);

	Rect botRC = Rect();
	botRC.SetSize(Vector3(Math::Abs(botSprite.getSize()->x * botSprite.getScale()->x), Math::Abs(botSprite.getSize()->y * botSprite.getScale()->y), 1));
	botRB = RigidBody();
	botRB.Initialize(1, 0, botSprite.getPos(), botSprite.getRot(), botSprite.getScale(), botSprite.getSize(), botRC);

	//moves the pipes
	topRB.AddForce(Vector3(-speed, 0, 0));
	botRB.AddForce(Vector3(-speed, 0, 0));
}

void Pipe::SetGap(float _gap)
{
	gap = _gap;
	UpdatePos();
}

float Pipe::GetPrevPos()
{
	return prevPos;
}

void Pipe::Update()
{
	prevPos = topSprite.getPos()->x;
	topRB.Update();
	botRB.Update();
}

void Pipe::Render()
{
	topSprite.Render();
	botSprite.Render();
	topRB.Render(Vector3(255, 0, 0));
	botRB.Render(Vector3(0, 0, 255));
}

void Pipe::MoveTo(Vector3 to)
{
	pos = to;
	UpdatePos();
}

void Pipe::MoveBy(Vector3 by)
{
	pos = pos + by;
	UpdatePos();
}

float Pipe::GetX()
{
	return topSprite.getPos()->x;
}

float Pipe::GetWidth()
{
	return topSprite.getSize()->x * topSprite.getScale()->x;
}

void Pipe::UpdatePos()
{
	Vector3 topPos = pos;
	topPos.y += (gap / 2) + Math::Abs(topSprite.getSize()->y * topSprite.getScale()->y / 2);
	topSprite.MoveTo(topPos);

	Vector3 botPos = pos;
	botPos.y -= (gap / 2) + Math::Abs(botSprite.getSize()->y * botSprite.getScale()->y / 2);
	botSprite.MoveTo(botPos);
}

RigidBody Pipe::GetTopRB()
{
	return topRB;
}

RigidBody Pipe::GetBotRB()
{
	return botRB;
}

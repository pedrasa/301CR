#include "Sprite.h"
#include "Engine.h"
#include "Vector3.h"
//sprite class, handles the texture to sprite transition and makes it so it follows the object
Sprite::Sprite()
{
	pos = Vector3(0);
	rot = 0;
	speed = 100;
	texture = Texture();
	size = Vector3(0);
	scale = Vector3(1);
}

Sprite::Sprite(string imagePath)
{
	texture = Texture(imagePath);
	pos = Vector3(0);
	scale = Vector3(1);
	size = Vector3((float)texture.getWidth(), (float)texture.getHeight(), 1);
	speed = 100;
	rot = 0;
}

Sprite::Sprite(string imagePath, Vector3 _Pos)
{
	texture = Texture(imagePath);
	pos = _Pos;
	scale = Vector3(1);
	size = Vector3((float)texture.getWidth(), (float)texture.getHeight(), 1);
	speed = 100;
	rot = 0;
}

void Sprite::Update()
{
	
}

void Sprite::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.getID());
	glLoadIdentity();

	//trans - rotate - scale
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(rot, 0, 0, 1);
	glScalef(scale.x, scale.y, 1);

	//rend
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);		glVertex2i(-texture.getWidth() / 2, -texture.getHeight() / 2);
		glTexCoord2f(1, 0);		glVertex2i(texture.getWidth() / 2, -texture.getHeight() / 2);
		glTexCoord2f(1, 1);		glVertex2i(texture.getWidth() / 2, texture.getHeight() / 2);
		glTexCoord2f(0, 1);		glVertex2i(-texture.getWidth() / 2, texture.getHeight() / 2);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Sprite::SpeedTo(float x)
{
	speed = x;
}

void Sprite::SpeedBy(float x)
{
	speed += x;
}

void Sprite::MoveTo(Vector3 vector)
{
	pos = vector;
}

void Sprite::MoveBy(Vector3 vector)
{
	pos = pos + (vector * Engine::getDT());
}

void Sprite::MoveLeft()
{
	pos = pos - Vector3((speed * Engine::getDT()),0,0);
}

void Sprite::MoveRight()
{
	pos = pos + Vector3((speed * Engine::getDT()), 0, 0);
}

void Sprite::MoveUp()
{
	pos = pos + Vector3(0,(speed * Engine::getDT()), 0);
}

void Sprite::MoveDown()
{
	pos = pos - Vector3(0, (speed * Engine::getDT()), 0);
}

void Sprite::RotateTo(float x)
{
	rot = x;
}

void Sprite::RotateBy(float x)
{
	rot += (x * Engine::getDT());
}

void Sprite::SetScale(float x)
{
	scale = Vector3(x);
}

void Sprite::SetScale(Vector3 vector)
{
	scale = vector;
}

void Sprite::FlipHorizontal()
{
	scale.x = -scale.x;
}

void Sprite::FlipVertical()
{
	scale.y = -scale.y;
}

Vector3* Sprite::getPos()
{
	return &pos;
}

float* Sprite::getRot()
{
	return &rot;
}

Vector3* Sprite::getScale()
{
	return &scale;
}

Vector3* Sprite::getSize()
{
	return &size;
};

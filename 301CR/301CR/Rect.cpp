#include "Rect.h"

#include <sstream>
//bounding boxes with the vertices being updates constantly, this is used in the creation of the rigidbody and collision detection
Rect::Rect()
{
	pos = Vector3(0);
	size = Vector3(0);
	updateVertices();
}

Rect::Rect(Vector3 _size) : Rect()
{
	pos = Vector3(0);
	size = _size;
	updateVertices();
}

Rect::Rect(Vector3 _pos, Vector3 _size) : Rect(_size)
{
	pos = _pos;
	updateVertices();
}

void Rect::MoveBy(Vector3 by)
{
	pos = pos + by;
	updateVertices();
}

void Rect::MoveTo(Vector3 to)
{
	pos = to;
	updateVertices();
}

void Rect::SetSize(Vector3 _size)
{
	size = _size;
	updateVertices();
}

string Rect::ToString()
{
	//this is a debug method to check the vertex to just in case you cant  draw the boxes properly
	stringstream ss;
	ss << "Pos(" << pos.x << ", " << pos.y << ", " << pos.z << ") - Size(" << size.x << ", " << size.y << ", " << size.z << ")" << endl;
	ss << "LL.X: " << lowerLeftVertex.x << "\tY: " << lowerLeftVertex.y << endl;
	ss << "UR.X: " << upperRightVertex.x << "\tY: " << upperRightVertex.y;
	return ss.str();
}

void Rect::updateVertices()
{
	//if you dont call this whenever anything that changes the rect happens it wont do anything to the box and it will apear blank, the to string method 
	//still useful incase something goes wrong
	upperLeftVertex = Vector3(pos.x - (size.x/2), pos.y + (size.y / 2),0);
	upperRightVertex = Vector3(pos.x + (size.x / 2), pos.y + (size.y / 2), 0);
	lowerLeftVertex = Vector3(pos.x - (size.x / 2), pos.y - (size.y / 2), 0);
	lowerRightVertex = Vector3(pos.x + (size.x / 2), pos.y - (size.y / 2), 0);
}

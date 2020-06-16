#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

class textureChanger
{
public:
	textureChanger();
	~textureChanger();
	void ChangeFlappyTexture();
	string getFileFlappy();
private:
	ifstream inFileFlappy;
	string newFlappy;
};


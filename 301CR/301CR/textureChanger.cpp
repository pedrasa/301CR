#include "textureChanger.h"


textureChanger::textureChanger()
{

}

textureChanger::~textureChanger()
{
}


void textureChanger::ChangeFlappyTexture()
{
	//inFileFlappy.open("C:\\301CR\\301CR\\textureFlappy.txt");
	inFileFlappy.open("C:\\Users\\Desktop\\Desktop\\301CR\\301CR\\textureFlappy.txt");
	if (!inFileFlappy) {
		cout << "Unable to open file textureFlappy.txt";
		exit(1);   // call system to stop
	}
	newFlappy.assign((std::istreambuf_iterator<char>(inFileFlappy)),
		(std::istreambuf_iterator<char>()));
	inFileFlappy.close();
}


string textureChanger::getFileFlappy()
{
	return newFlappy;
}

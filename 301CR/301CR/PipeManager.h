#pragma once
#include "Pipe.h"
#include "Flapper.h"
#include "Audio.h"
#include <vector>
using namespace std;

class PipeManager
{
public:
	PipeManager();
	~PipeManager();

	void Update();
	void Render();

	bool CheckCollision(Flapper& flapper);

	void Reset();

private:
	void CreatePipe();

private:
	vector<Pipe*> pipes;
	Audio* mAudio;

	//all the variables that make sure the pipes stay far enough away so that its fair but challening
	float xStartSeparation;//the firsts pipe seperation
	float yStartSeparation;
	float xSeparation;
	float ySeparation;
	float minXSeparation;
	float minYSeparation;
	float xSeparationSpeed;
	float ySeparationSpeed;

	int minSpawnY;
	int maxSpawnY;

	int totalPipes;
	int points;
};



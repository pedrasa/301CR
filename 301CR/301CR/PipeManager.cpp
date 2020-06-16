#include "PipeManager.h"

#include "Engine.h"
#include "RigidBody.h"

//its manages all pipes in the level, creating pipes until the player fails the game and collides with the pipe
PipeManager::PipeManager() : 
	xStartSeparation(800),
	yStartSeparation(500),
	xSeparation(xStartSeparation),
	ySeparation(yStartSeparation),
	minXSeparation(200),
	minYSeparation(300),
	xSeparationSpeed(10),
	ySeparationSpeed(100),
	minSpawnY(284),
	maxSpawnY(Engine::SCREEN_HEIGHT - 284),//so they dont spawn off view
	totalPipes(0),
	points(0)
{
	mAudio = new Audio("Score.wav");
	Pipe::Initialize();
	CreatePipe();
}

PipeManager::~PipeManager()
{
	for (unsigned int i = 0; i < pipes.size(); i++)
	{
		delete pipes[i];
	}
}

void PipeManager::Update()
{
	vector<int> pipesToDelete;
	for (unsigned int i = 0; i < pipes.size(); i++) //checking all pipes to update and render
	{
		pipes[i]->Update();
		if (pipes[i]->GetX() < -(pipes[i]->GetWidth() / 2))//checks if the pipe is off screeen
		{
			pipesToDelete.push_back(i);
		}

		if (i == pipes.size() - 1) //this means we are checking the last pipe
			//told to create new pipes using the xSperation to make them closer together over time
		{
			if (pipes[i]->GetX() < Engine::SCREEN_WIDTH - xSeparation)
			{
				CreatePipe();
			}
		}

		if (pipes[i]->GetX() < Engine::SCREEN_WIDTH / 2 &&
			pipes[i]->GetPrevPos() > Engine::SCREEN_WIDTH / 2)
		{
			points++; //if the pipes passed this then the player did not hit them
			mAudio->Play();
		}
	}

	for (unsigned int i = 0; i < pipesToDelete.size(); i++)//delete the pipes to delete
	{
		delete pipes[pipesToDelete[i]];
		pipes.erase(pipes.begin() + pipesToDelete[i]);
	}

	//cout << "Points: " << points << endl;
}

void PipeManager::Render()
{
	for (unsigned int i = 0; i < pipes.size(); i++)
	{
		pipes[i]->Render();
		mAudio->system->update();
	}
}

bool PipeManager::CheckCollision(Flapper& flapper) // checks the collision between the player and the pipes
{
	bool isColliding = false;

	for (unsigned int i = 0; i < pipes.size(); i++)
	{
		isColliding = RigidBody::IsColliding(flapper.getRB(), pipes[i]->GetTopRB()) || RigidBody::IsColliding(flapper.getRB(), pipes[i]->GetBotRB());
		if (isColliding)
			break;
	}

	return isColliding;
}

void PipeManager::Reset() // reset used for new level and restart
{
	for (unsigned int i = 0; i < pipes.size(); i++)
	{
		delete pipes[i];
	}
	pipes.clear();

	xSeparation = xStartSeparation;
	ySeparation = yStartSeparation;
	totalPipes = 0;
	points = 0;

	CreatePipe();
}

// Private

void PipeManager::CreatePipe()
{
	//random number to spawn pipes, then use a new functon to create the pipes, and finaly set the gap inbetween them
	float spawnY = (rand() % (maxSpawnY - minSpawnY)) + minSpawnY; //number from 5 to 10
	Pipe* pipe = new Pipe(Vector3(Engine::SCREEN_WIDTH, spawnY, 0));
	pipe->SetGap(ySeparation);

	pipes.push_back(pipe);
	totalPipes++;
	//this also checks every two pipes
	if (totalPipes % 2 == 0)//this increases the diffculty of the gaps by making them smalller until they the minimum allowed
	{
		if (xSeparation > minXSeparation + xSeparationSpeed)
		{
			xSeparation -= xSeparationSpeed;
		}

		if (ySeparation > minYSeparation + ySeparationSpeed)
		{
			ySeparation -= ySeparationSpeed;
		}
	}
}
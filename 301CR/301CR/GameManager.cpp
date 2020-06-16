#include "GameManager.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Audio.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include <enet\enet.h>
#include <Box2D\Box2D.h>

using namespace std;

GameManager::GameManager()//handles our game loop, usable to create level 2
{
	mEngine = new Engine();
	mEngine->Initialize("301CR");

	Sprite testSprite = Sprite("Textures/Biplane.png", Vector3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	testSprite.SetScale(0.15f);

	mFlapper = new Flapper(testSprite);
	mPipeManager = new PipeManager();
	mserverManager = new serverManager();
	mtextureChanger = new textureChanger();

	mAudio = new Audio("Die.wav");
	mAudio1 = new Audio("Background.wav");

	mAudio1->ChangeSoundLevel(40.0f); //use this to change background music sound level

	mStartSprite = Sprite("Textures/spacetostart.png", Vector3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	mGameoverSprite = Sprite("Textures/gameover.png", Vector3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	mGameoverSprite.SetScale(0.15f);

	mState = State::START;
}

GameManager::~GameManager()
{
	delete mEngine;
	delete mFlapper;
	delete mPipeManager;
	delete mserverManager;
}

void GameManager::Start()
{


	while (true)//this is the game loop
	{
		if (Keyboard::keyDown(GLFW_KEY_ESCAPE))
		{
			break;
		}

		mEngine->Update();

		switch (mState)
		{
		case State::START:
		{
			mEngine->BeginRender();
			mStartSprite.Render();
			mEngine->EndRender();
			mserverManager->connect();

			if (Keyboard::keyDown(GLFW_KEY_SPACE) || Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT))
			{
				SetState(State::GAMEPLAY);
			}
			if (Keyboard::keyDown(GLFW_KEY_UP))
			{
				mtextureChanger->ChangeFlappyTexture();
				Sprite testSprite = Sprite(mtextureChanger->getFileFlappy() , Vector3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
				testSprite.SetScale(0.15f);
				mFlapper = new Flapper(testSprite);
			}
		}
		break;
		case State::GAMEPLAY:
		{
			mFlapper->Update();
			mPipeManager->Update();
			mAudio->system->update();
			mAudio1->system->update();
			mAudio1->Play();
			mEngine->BeginRender();
			mPipeManager->Render();
			mFlapper->Render();
			mEngine->EndRender();


			bool isDead = mPipeManager->CheckCollision(*mFlapper);
			if (mFlapper->getSprite().getPos()->y < 0 || mFlapper->getSprite().getPos()->y > Engine::SCREEN_HEIGHT)
			{
				isDead = true;
			}
			if (isDead)
			{
				mAudio->Play();
				SetState(State::GAMEOVER);
			}
		}
		break;
		case State::GAMEOVER:
		{
			mEngine->BeginRender();
			mPipeManager->Render();
			mFlapper->Render();
			mGameoverSprite.Render();
			mEngine->EndRender();
			mserverManager->disconnect();

			if (Keyboard::keyDown(GLFW_KEY_SPACE) || Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT))
			{
				SetState(State::START);
			}
		}
		break;
		default:
			cout << "Unhandled game state: " << static_cast<int>(mState) << endl;
			break;
		}
	}
}

// Private

void GameManager::SetState(State state)
{
	mState = state;

	if (mState == State::START)
	{
		mFlapper->Reset();
		mPipeManager->Reset();
	}
}
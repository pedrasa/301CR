#pragma once
#include "Engine.h"
#include "Sprite.h"
#include "Audio.h"
#include "Flapper.h"
#include "PipeManager.h"
#include "serverManager.h"
#include "textureChanger.h"


class GameManager
{
public:
	enum class State
	{
		START,
		GAMEPLAY,
		GAMEOVER,
		COUNT
	};

public:
	GameManager();
	~GameManager();

	void Start();

private:
	void SetState(State state);

private:
	Engine* mEngine;
	Flapper* mFlapper;
	Audio* mAudio;
	Audio* mAudio1;
	PipeManager* mPipeManager;
	serverManager* mserverManager;
	textureChanger* mtextureChanger;

	Sprite mStartSprite;
	Sprite mGameoverSprite;

	State mState;
};


#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 80.5f);
	mPlayerOneScore = new Scoreboard(28);
	mTopScore = new Scoreboard(16);
	mLifeOne = new Texture("Asteroids.png", 0, 50, 13, 15);
	mLifeTwo = new Texture("Asteroids.png", 0, 50, 13, 15);
	mLifeThree = new Texture("Asteroids.png", 0, 50, 13, 15);

	mTopBar->Parent(this);
	mPlayerOneScore->Parent(mTopBar);
	mTopScore->Parent(mTopBar);
	mLifeOne->Parent(mTopBar);
	mLifeTwo->Parent(mTopBar);
	mLifeThree->Parent(mTopBar);

	mPlayerOneScore->Position(-Graphics::SCREEN_WIDTH * 0.38f, 40.0f);
	mTopScore->Position(Graphics::SCREEN_WIDTH * 0.05f, 40.0f);
	mLifeOne->Position(-Graphics::SCREEN_WIDTH * 0.42f, 70.0f);
	mLifeTwo->Position(-Graphics::SCREEN_WIDTH * 0.40f, 70.0f);
	mLifeThree->Position(-Graphics::SCREEN_WIDTH * 0.38f, 70.0f);

	mLifeOne->Scale(Vector2(2, 2));
	mLifeTwo->Scale(Vector2(2, 2));
	mLifeThree->Scale(Vector2(2, 2));

	mTopScore->Score(00);
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mAsteroid;
	mAsteroid = nullptr;

	delete mTopBar;
	mTopBar = nullptr;
	delete mPlayerOneScore;
	mPlayerOneScore = nullptr;
	delete mTopScore;
	mTopScore = nullptr;

	delete mLifeOne;
	mLifeOne = nullptr;
	delete mLifeTwo;
	mLifeTwo = nullptr;
	delete mLifeThree;
	mLifeThree = nullptr;
}

void PlayScreen::Start()
{
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.8f);
	mPlayer->Active(true);

	delete mAsteroid;
	mAsteroid = new Asteroid();
	mAsteroid->Parent(this);
	mAsteroid->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.3f);
	mAsteroid->Active(true);
	mAsteroid->SetId(PhysicsManager::Instance()->RegisterEntity(mAsteroid, PhysicsManager::CollisionLayers::Hostile));
}

void PlayScreen::Update() {
	mPlayerOneScore->Update();
	mTopScore->Update();

	mLifeOne->Update();
	mLifeTwo->Update();
	mLifeThree->Update();

	mPlayer->Update();
	mAsteroid->Update();
}

void PlayScreen::Render() {
	mPlayerOneScore->Render();
	mTopScore->Render();

	if (mPlayer->Lives() >= 1)
	{
		mLifeOne->Render();
		if (mPlayer->Lives() >= 2)
		{
			mLifeTwo->Render();
			if (mPlayer->Lives() >= 3)
			{
				mLifeThree->Render();
			}
		}
	}
	
	mPlayer->Render();
	mAsteroid->Render();
	
}

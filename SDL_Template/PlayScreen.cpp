#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mRandom = Random::Instance();
	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 80.5f);
	mPlayerOneScore = new Scoreboard(28);
	mTopScore = new Scoreboard(16);
	mLifeOne = new Texture("Asteroids.png", 0, 50, 13, 15);
	mLifeTwo = new Texture("Asteroids.png", 0, 50, 13, 15);
	mLifeThree = new Texture("Asteroids.png", 0, 50, 13, 15);
	mScore = 0;
	mTopBar->Parent(this);
	mPlayerOneScore->Parent(mTopBar);
	mTopScore->Parent(mTopBar);
	mLifeOne->Parent(mTopBar);
	mLifeTwo->Parent(mTopBar);
	mLifeThree->Parent(mTopBar);

	mPlayerOneScore->Position(-Graphics::SCREEN_WIDTH * 0.30f, 40.0f);
	mTopScore->Position(Graphics::SCREEN_WIDTH * 0.05f, 40.0f);
	mLifeOne->Position(-Graphics::SCREEN_WIDTH * 0.42f, 70.0f);
	mLifeTwo->Position(-Graphics::SCREEN_WIDTH * 0.40f, 70.0f);
	mLifeThree->Position(-Graphics::SCREEN_WIDTH * 0.38f, 70.0f);

	mLifeOne->Scale(Vector2(2, 2));
	mLifeTwo->Scale(Vector2(2, 2));
	mLifeThree->Scale(Vector2(2, 2));

	mTopScore->Score(00);
	
	for (int i = 0; i < mClusterMax; i++)
	{
		mCluster.push_back(new Asteroid(2, this));

		Vector2 position;
		do {
			position.x = mRandom->RandomRange(0.0f, (float)Graphics::SCREEN_WIDTH);
			position.y = mRandom->RandomRange(0.0f, (float)Graphics::SCREEN_HEIGHT);
		} while (position.x > 128 && position.x < 896 && position.y > 128 && position.y < 768);

		mCluster.back()->Position(position.x, position.y);
	}
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	//delete the excess asteroids
	for (int i = 0; i <= mCluster.size() - 1; i++)
	{
		delete mCluster[i];
		mCluster[i] = nullptr;
	}

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

}

void PlayScreen::Update() {
	mPlayerOneScore->Update();
	mTopScore->Update();

	mLifeOne->Update();
	mLifeTwo->Update();
	mLifeThree->Update();

	mPlayer->Update(); 
	if (mPlayer->Lives() < 1) {
		mTopScore->Score(mScore);
	}
	
	for (auto a : mCluster)
	{
		a->Update();
	}

	if (mCluster.empty())
	{
		for (int i = 0; i < mClusterMax; i++)
		{
			mCluster.push_back(new Asteroid(1, this));

			Vector2 position;
			do {
				position.x = mRandom->RandomRange(0.0f, (float)Graphics::SCREEN_WIDTH);
				position.y = mRandom->RandomRange(0.0f, (float)Graphics::SCREEN_HEIGHT);
			} while (position.x > 128 && position.x < 896 && position.y > 128 && position.y < 768);

			mCluster.back()->Position(position.x, position.y);
			mScore += 1000;
		}
	}

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
	
	for (auto a : mCluster)
	{
		a->Render();
	}

	mPlayer->Render();

}
void PlayScreen::SpawnAsteroid(int size, Vector2 position, Asteroid* asteroid)
{
	if (size == 2)
	{
		mScore += 20;
		mPlayerOneScore->Score(mScore);
		mCluster.push_back(new Asteroid(1, this));
		mCluster.back()->Position(position);
		mCluster.push_back(new Asteroid(1, this));
		mCluster.back()->Position(position);

		auto it = std::find(mCluster.begin(), mCluster.end(), asteroid);
		if (it != mCluster.end())
		{
			mCluster.erase(it);
			delete asteroid;
		}
	}
	if (size == 1)
	{
		mScore += 50;
		mPlayerOneScore->Score(mScore);
		mCluster.push_back(new Asteroid(0, this));
		mCluster.back()->Position(position);
		mCluster.push_back(new Asteroid(0, this));
		mCluster.back()->Position(position);

		auto it = std::find(mCluster.begin(), mCluster.end(), asteroid);
		if (it != mCluster.end())
		{
			mCluster.erase(it);
			delete asteroid;
		}
	}if (size == 0)
	{
		mScore += 100;
		mPlayerOneScore->Score(mScore);
		auto it = std::find(mCluster.begin(), mCluster.end(), asteroid);
		if (it != mCluster.end())
		{
			mCluster.erase(it);
			delete asteroid;
		}
	}
}


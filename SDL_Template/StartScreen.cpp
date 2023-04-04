#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mRandom = Random::Instance();

	// top bar entities
	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 80.5f);
	mPlayerOneScore = new Scoreboard(28);
	mTopScore = new Scoreboard(16);

	mTopBar->Parent(this);
	mPlayerOneScore->Parent(mTopBar);
	mTopScore->Parent(mTopBar);

	mPlayerOneScore->Position(-Graphics::SCREEN_WIDTH * 0.38f, 40.0f);
	mTopScore->Position(Graphics::SCREEN_WIDTH * 0.05f, 40.0f);

	mTopScore->Score(00);

	// logo entities
	mLogo = new Texture("PUSH START", "HyperspaceBold-GM0g.ttf", 24, { 255, 255, 255 });
	
	mLogo->Parent(this);

	mLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.2f);

	// play mode entities
	mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f);

	mPlayModes->Parent(this);

	// bottom bar entities
	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
	mDates = new Texture("1 COIN 1 PLAY", "HyperspaceBold-GM0g.ttf", 28, { 230, 230, 230 });
	mRights = new Texture("©1979 ATARI INC", "HyperspaceBold-GM0g.ttf", 16, { 230, 230, 230 });

	mBottomBar->Parent(this);
	mDates->Parent(mBottomBar);
	mRights->Parent(mBottomBar);

	mDates->Position(0.0f, 90.0f);
	mRights->Position(0.0f, 170.0f);

	//Asteroid entities
	mAsteroid1 = new Asteroid();
	mAsteroid2 = new Asteroid();
	mAsteroid3 = new Asteroid();
	mAsteroid4 = new Asteroid();

	mAsteroid1->Parent(this);
	mAsteroid2->Parent(this);
	mAsteroid3->Parent(this);
	mAsteroid4->Parent(this);
	
	mAsteroid1->Position(mRandom->RandomRange(0, Graphics::SCREEN_WIDTH), mRandom->RandomRange(0, Graphics::SCREEN_HEIGHT));
	mAsteroid2->Position(mRandom->RandomRange(0, Graphics::SCREEN_WIDTH), mRandom->RandomRange(0, Graphics::SCREEN_HEIGHT));
	mAsteroid3->Position(mRandom->RandomRange(0, Graphics::SCREEN_WIDTH), mRandom->RandomRange(0, Graphics::SCREEN_HEIGHT));
	mAsteroid4->Position(mRandom->RandomRange(0, Graphics::SCREEN_WIDTH), mRandom->RandomRange(0, Graphics::SCREEN_HEIGHT));
}


StartScreen::~StartScreen() {
	// top bar entities
	delete mTopBar;
	mTopBar = nullptr;
	delete mPlayerOneScore;
	mPlayerOneScore = nullptr;
	delete mTopScore;
	mTopScore = nullptr;

	// logo entities
	delete mLogo;
	mLogo = nullptr;

	// play mode entities
	delete mPlayModes;
	mPlayModes = nullptr;

	// bottom bar entities
	delete mBottomBar;
	mBottomBar = nullptr;
	delete mDates;
	mDates = nullptr;
	delete mRights;
	mRights = nullptr;

	//Asteroid entities
	delete mAsteroid1;
	mAsteroid1 = nullptr;
	delete mAsteroid2;
	mAsteroid2 = nullptr;
	delete mAsteroid3;
	mAsteroid3 = nullptr;
	delete mAsteroid4;
	mAsteroid4 = nullptr;

	mRandom = nullptr;
	mTimer = nullptr;
	mInput = nullptr;
}

void StartScreen::CleanUp()
{
	PhysicsManager::Instance()->UnregisterEntity(mAsteroid1->GetId());
	PhysicsManager::Instance()->UnregisterEntity(mAsteroid2->GetId());
	PhysicsManager::Instance()->UnregisterEntity(mAsteroid3->GetId());
	PhysicsManager::Instance()->UnregisterEntity(mAsteroid4->GetId());
}

void StartScreen::Update() {
	if (animTimer <= 50)
	{
		animTimer++* mTimer->DeltaTime();
	}
	else
	{
		if (animTime)
		{
			animTime = false;
		}
		else if (!animTime)
		{
			animTime = true;
		}
		animTimer = 0;
	}
	mAsteroid1->Update();
	mAsteroid2->Update();
	mAsteroid3->Update();
	mAsteroid4->Update();
}

void StartScreen::Render() {
	mPlayerOneScore->Render();
	mTopScore->Render();

	if (animTime)
	{
		mLogo->Render();
	}

	mDates->Render();
	mRights->Render();
	
	mAsteroid1->Render();
	mAsteroid2->Render();
	mAsteroid3->Render();
	mAsteroid4->Render();
}
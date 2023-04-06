#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 80.5f);
	mPlayerOneScore = new Scoreboard(28);
	mTopScore = new Scoreboard(16);

	mTopBar->Parent(this);
	mPlayerOneScore->Parent(mTopBar);
	mTopScore->Parent(mTopBar);

	mPlayerOneScore->Position(-Graphics::SCREEN_WIDTH * 0.38f, 40.0f);
	mTopScore->Position(Graphics::SCREEN_WIDTH * 0.05f, 40.0f);

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
	mPlayer->Update();
	mAsteroid->Update();
}

void PlayScreen::Render() {
	mPlayerOneScore->Render();
	mTopScore->Render();
	
	mPlayer->Render();
	mAsteroid->Render();
	
}

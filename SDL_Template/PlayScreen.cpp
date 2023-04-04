#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

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

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mAsteroid;
	mAsteroid = nullptr;
}

void PlayScreen::Update() {
	mPlayer->Update();
	mAsteroid->Update();
}

void PlayScreen::Render() {
	mPlayer->Render();
	mAsteroid->Render();
}

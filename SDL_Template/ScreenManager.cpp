 #include "ScreenManager.h"

ScreenManager * ScreenManager::sInstance = nullptr;

ScreenManager * ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void ScreenManager::Anykey(){
	if (!mStarted)
	{
		mCurrentScreen = Play;
		mStartScreen->CleanUp();
		mPlayScreen->Start();
		mStarted = true;
	}
}

void ScreenManager::Update() {

	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Update();
		break;
	case Play:
		mPlayScreen->Update();
		break;
	}
}

void ScreenManager::Render() { 
	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Render();
		break;
	case Play:
		mPlayScreen->Render();
		break;
	}
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();


	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mCurrentScreen = Start;
	mStarted = false;
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;
}
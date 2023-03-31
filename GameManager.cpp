#include "GameManager.h"

namespace SDLFramework {

	GameManager* GameManager::sInstance = nullptr;
	GameManager* GameManager::Instance()
	{
		if (sInstance == nullptr) {
			sInstance = new GameManager();
		}
		return sInstance;
	}

	void GameManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	void GameManager::Run() {
		// main game loop
		while (!mQuit) {
			mTimer->Update();
			// event processing loop
			while (SDL_PollEvent(&mEvent)) {
				switch (mEvent.type) {
				case SDL_QUIT:
					mQuit = true;
					break;
				}
			}
			if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {
				mTimer->Reset();
				Update();
				LateUpdate();
				Render();
			}
		}
	}

	void GameManager::Update() {
		mInputManager->Update();

		mScreenManager->Update();
	}

	void GameManager::LateUpdate() {
		mInputManager->UpdatePrevInput();
	}
	void GameManager::Render() {
		mGraphics->ClearBackBuffer();
		mScreenManager->Render();
		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false) {
		// create Graphics singleton
		mGraphics = GraphicsManager::Instance();

		// verify Graphics module is ready
		if (!GraphicsManager::Initialized()) {
			mQuit = true;
		}

		mAssetManager = AssetManager::Instance();
		mInputManager = InputManager::Instance();
		mAudioManager = AudioManager::Instance();
		mScreenManager = ScreenManager::Instance();

		mTimer = Timer::Instance();
	}

	GameManager::~GameManager() {
		// release modules
		Timer::Release();
		mTimer = nullptr;

		ScreenManager::Release();
		mScreenManager = nullptr;

		AudioManager::Release();
		mAudioManager = nullptr;

		InputManager::Release();
		mInputManager = nullptr;

		AssetManager::Release();
		mAssetManager = nullptr;

		GraphicsManager::Release();
		mGraphics = nullptr;

		// Quit SDL subsystems
		SDL_Quit();
	}
}

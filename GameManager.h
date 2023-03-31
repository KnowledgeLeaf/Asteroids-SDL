#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H
#include "Timer.h"
#include "GameEntity.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "ScreenManager.h"

namespace SDLFramework {

	class GameManager {
	private:
		const int FRAME_RATE = 60;
		Timer* mTimer;

		// singleton
		static GameManager* sInstance;

		// loop control
		bool mQuit;

		// modules
		GraphicsManager* mGraphics;
		AssetManager* mAssetManager;
		InputManager* mInputManager;
		AudioManager* mAudioManager;
		ScreenManager* mScreenManager;

		SDL_Event mEvent;

	public:
		static GameManager* Instance();
		static void Release();

		void Run();
		void Update();
		void LateUpdate();
		void Render();
		GameManager();
		~GameManager();
	};

}
#endif
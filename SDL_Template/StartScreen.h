#ifndef __STARTSCREEN_H
#define __STARTSCREEN_H
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "Scoreboard.h"
#include "Random.h"
#include "Asteroid.h"
#include "PhysicsManager.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {

private:
	Timer * mTimer;
	InputManager * mInput;
	Random * mRandom;

	float animTimer;
	bool animTime = false;

	// Top Bar Entities
	GameEntity * mTopBar;
	Texture * mPlayerOne;
	Texture * mPlayerTwo;
	Texture * mHiScore;
	Scoreboard * mPlayerOneScore;
	Scoreboard * mPlayerTwoScore;
	Scoreboard * mTopScore;

	// Logo Entities
	Texture * mLogo;
	AnimatedTexture * mAnimatedLogo;

	// Play Mode Entities
	GameEntity * mPlayModes;
	Texture * mOnePlayerMode;
	Texture * mTwoPlayerMode;
	Texture * mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;

	// Bottom Bar Entities
	GameEntity * mBottomBar;
	Texture * mNamco;
	Texture * mDates;
	Texture * mRights;

	// Screen Animation Variables
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

	//Asteroids
	Asteroid* mAsteroid1;
	Asteroid* mAsteroid2;
	Asteroid* mAsteroid3;
	Asteroid* mAsteroid4;

public:
	StartScreen();
	~StartScreen();

	int SelectedMode();
	void CleanUp();

	void Update() override;
	void Render() override;
};
#endif
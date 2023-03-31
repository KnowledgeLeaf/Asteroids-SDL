#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "AudioManager.h"
#include "BackgroundStars.h"
#include "PlaySideBar.h"
#include "Level.h"
#include "Player.h"

class PlayScreen : public GameEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;
	BackgroundStars* mStars;
	PlaySideBar* mSideBar;

	Texture* mStartLabel;
	float mLevelStartTimer;
	float mLevelStartDelay;
	bool mGameStarted;
	Level* mLevel;
	bool mLevelStarted;
	int mCurrentStage;

	Player* mPlayer;

public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();
	bool GameOver();

	void Update() override;
	void Render() override;

private:
	void StartNextLevel();
};
#endif

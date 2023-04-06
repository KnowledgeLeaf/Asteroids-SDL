#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "Player.h"
#include "Asteroid.h"
#include "Scoreboard.h"

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	AudioManager * mAudio;

	Player * mPlayer;
	Asteroid * mAsteroid;
	Texture* mHiScore;
	GameEntity* mTopBar;
	Scoreboard* mPlayerOneScore;
	Scoreboard* mPlayerTwoScore;
	Scoreboard* mTopScore;

public:
	PlayScreen();
	~PlayScreen();

	void Start();
	void Update() override;
	void Render() override;
};
#endif
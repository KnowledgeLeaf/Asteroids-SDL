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
	Asteroid * mAsteroid1;
	Asteroid * mAsteroid2; 
	Asteroid * mAsteroid3; 
	Asteroid * mAsteroid4;
	Texture* mHiScore;
	GameEntity* mTopBar;
	Scoreboard* mPlayerOneScore;
	Scoreboard* mPlayerTwoScore;
	Scoreboard* mTopScore;
	Texture* mLifeOne;
	Texture* mLifeTwo;
	Texture* mLifeThree;

public:
	PlayScreen();
	~PlayScreen();

	void Start();
	void Update() override;
	void Render() override;

};
#endif
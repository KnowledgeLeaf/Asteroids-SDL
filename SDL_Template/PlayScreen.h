#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "Player.h"
#include "Asteroid.h"

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	AudioManager * mAudio;

	Player * mPlayer;
	Asteroid * mAsteroid;


public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;
};
#endif
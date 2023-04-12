#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "Player.h"
#include "Asteroid.h"
#include "Scoreboard.h"
#include "Fmissiles.h"
#include "Random.h"
#include <vector>

class PlayScreen : public GameEntity {
private:
	Timer * mTimer; 
	Random* mRandom;
	AudioManager * mAudio;

	Player * mPlayer;
	std::vector<Asteroid*> mCluster;

	Texture* mHiScore;
	GameEntity* mTopBar;
	Scoreboard* mPlayerOneScore;
	Scoreboard* mPlayerTwoScore;
	Scoreboard* mTopScore;
	Texture* mLifeOne;
	Texture* mLifeTwo;
	Texture* mLifeThree; 
	static const int mClusterMax = 4;

public:
	PlayScreen();
	~PlayScreen();

	void Start();
	void Update() override;
	void Render() override;
	void SpawnAsteroid(int size, Vector2 position, Asteroid* asteroid);

};
#endif
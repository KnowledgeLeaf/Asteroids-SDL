#ifndef __ASTEROID_H
#define __ASTEROID_H
#include "PhysEntity.h"
#include "Random.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "Timer.h"
#include <vector>

class PlayScreen;

using namespace SDLFramework;

class Asteroid : public PhysEntity
{
private:
	PlayScreen* mPlayScreen;
	Timer * mTimer;
	Random * mRandom;
	Texture * asteroidTex;
	
	float mMoveSpeed;
	Vector2 mVelocity;
	Vector2 mMoveBoundsHorizontal;
	Vector2 mMoveBoundsVertical;
	int mAsteroidTextRand;
	int mSize;
	std::vector<int> mSpritePos;

	void HandleMovement();

public:
	Asteroid();
	Asteroid(int size, PlayScreen* playscreen);
	~Asteroid();
	
	
	
	void Hit(PhysEntity* other) override;

	void Update() override;
	void Render() override;
};
#endif
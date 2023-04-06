#ifndef __ASTEROID_H
#define __ASTEROID_H
#include "PhysEntity.h"
#include "Random.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "Timer.h"

using namespace SDLFramework;

class Asteroid : public PhysEntity
{
private:
	Timer * mTimer;
	Random * mRandom;

	Texture * asteroidTex;

	float mMoveSpeed;
	Vector2 mVelocity;
	Vector2 mMoveBoundsHorizontal;
	Vector2 mMoveBoundsVertical;

	void HandleMovement();

public:
	Asteroid();
	~Asteroid();

	void Hit(PhysEntity* other) override;

	void Update() override;
	void Render() override;
};
#endif
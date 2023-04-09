#ifndef __PLAYER_H
#define __PLAYER_H
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

using namespace SDLFramework;

class Player : public PhysEntity {
private:
	Timer * mTimer;
	InputManager * mInput;
	AudioManager * mAudio;
	
	Vector2 mVelocity;
	Vector2 mMoveBoundsHorizontal;
	Vector2 mMoveBoundsVertical;
	
	bool mVisible;
	bool mAnimating;
	bool mWasHit;

	int mScore;
	int mLives;

	Texture * mShip;
	AnimatedTexture * mDeathAnimation;
	Collider * mCollider;

	float mMoveSpeed;
	float mInvincibilityTime;
	float mInvincibilityTimer;
	bool mInvincible;
	

private:
	void HandleMovement();

public:
	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity * other) override;
	
	bool WasHit();

	void Update() override;
	void Render() override;
};
#endif
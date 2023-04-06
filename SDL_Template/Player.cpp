#include "Player.h"

void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		Rotate(150.0f * mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		Rotate(-150.0f * mTimer->DeltaTime());
	}

	if (mInput->KeyDown(SDL_SCANCODE_SPACE)) {
		Translate(-Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), Local);
	}

	Vector2 pos = Position(Local);
	if (pos.x < mMoveBoundsHorizontal.x) {
		pos.x = mMoveBoundsHorizontal.y;
	}
	else if (pos.x > mMoveBoundsHorizontal.y) {
		pos.x = mMoveBoundsHorizontal.x;
	}
	if (pos.y < mMoveBoundsVertical.x) {
		pos.y = mMoveBoundsVertical.y;
	}
	else if (pos.y > mMoveBoundsVertical.y) {
		pos.y = mMoveBoundsVertical.x;
	}
	

	Position(pos);
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = true;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 2;
	
	mShip = new Texture("Asteroids.png", 0, 50, 13, 15);
	mShip->Parent(this);
	mShip->Position(Vec2_Zero);
	mShip->Scale(Vector2(2, 2));

	mMoveSpeed = 300.0f;
	mMoveBoundsHorizontal = Vector2(0.0f, Graphics::SCREEN_WIDTH);
	mMoveBoundsVertical = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mDeathAnimation = new AnimatedTexture("PlayerExplosion.png", 0, 0, 128, 128, 4, 1.0f, AnimatedTexture::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(AnimatedTexture::Once);

	AddCollider(new BoxCollider(Vector2(16.0f, 16.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mShip;
	mShip = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

}

void Player::Visible(bool visible) {
	mVisible = visible;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

void Player::AddScore(int change) {
	mScore += change;
}

bool Player::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Player::Hit(PhysEntity * other) {
	mLives -= 1;
	mAnimating = true;
	mDeathAnimation->ResetAnimation();
	mAudio->PlaySFX("SFX/PlayerExplosion.wav");
	mWasHit = true;
}

bool Player::WasHit() {
	return mWasHit;
}

void Player::Update() {
	if (mAnimating) {

		if (mWasHit) {
			mWasHit = false;
		}

		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	}
	else {
		if (Active()) {
			HandleMovement();
		}
	}
}

void Player::Render() {
	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else {
			mShip->Render();
		}
	}

	PhysEntity::Render();
}

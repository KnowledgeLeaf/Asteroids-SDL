#include "Player.h"

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mRotateSpeed = 150.0f;
	mVelocity = Vec2_Zero;
	mMaxVelocity = 500.0f;
	mAcceleration = 200.0f;
	mVisible = true;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 3;

	mInvincibilityTime = 3;
	mInvincibilityTimer = 0;
	mInvincible = false;
	
	mShip = new Texture("Asteroids.png", 0, 50, 13, 15);
	mShip->Parent(this);
	mShip->Position(Vec2_Zero);
	mShip->Scale(Vector2(2, 2));

	mMoveSpeed = 300.0f;
	mMoveBoundsHorizontal = Vector2(0.0f, Graphics::SCREEN_WIDTH);
	mMoveBoundsVertical = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mDeathAnimation = new AnimatedTexture("Asteroids.png", 0, 60, 13, 15, 9, 1.0f, AnimatedTexture::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->Scale(Vector2(2, 2));
	mDeathAnimation->SetWrapMode(AnimatedTexture::Once);

	AddCollider(mCollider = new BoxCollider(Vector2(16.0f, 16.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	for (int i = 0; i < MAX_MISSILES; ++i) {
		mFmissiles[i] = new Fmissiles();
	}
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mShip;
	mShip = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

	for (int i = 0; i < MAX_MISSILES; ++i) {
		delete mFmissiles[i];
		mFmissiles[i] = nullptr;
	}
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

bool Player::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

bool Player::WasHit() {
	return mWasHit;
}

bool Player::IsAnimating() {
	return mAnimating;
}

void Player::AddScore(int change) {
	mScore += change;
}

void Player::HandleFiring() {
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
		for (int i = 0; i < MAX_MISSILES; ++i) {
			if (!mFmissiles[i]->Active()) {
				mFmissiles[i]->Fire(Position());
				mFmissiles[i]->Rotation(Rotation());
				//mAudio->PlaySFX("SFX/Fire.wav", 0, -1);
				std::cout << "FIRE!";
				break;
			}
		}
	}
}

void Player::HandleMovement() {
	Vector2 impulse = Vec2_Zero;
	
	if (mInput->KeyDown(SDL_SCANCODE_UP)) {
		impulse.x = mAcceleration * sin(Rotation() * DEG_TO_RAD) * mTimer->DeltaTime();
		impulse.y = mAcceleration * -cos(Rotation() * DEG_TO_RAD) * mTimer->DeltaTime();
		/*animated mImpulsed = true;*/
	}
	/*else {
		mImpulsed = false;
	}*/
	
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		Rotate(mRotateSpeed * mTimer->DeltaTime());
	}
	
	if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		Rotate(-mRotateSpeed * mTimer->DeltaTime());
	}
	
	Vector2 pos = Position(Local);
	
	mVelocity.x += impulse.x;
	mVelocity.y += impulse.y;
	//slowdown bro
	mVelocity = mVelocity * 0.995f;

	if (mVelocity.Magnitude() > mMaxVelocity) {
		mVelocity = mVelocity.Normalized() * mMaxVelocity;
	}
	
	pos.x += mVelocity.x * mTimer->DeltaTime();
	pos.y += mVelocity.y * mTimer->DeltaTime();

	//teleport piece
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

void Player::Hit(PhysEntity * other) {
	mLives -= 1;
	mAnimating = true;
	mDeathAnimation->ResetAnimation();
	//mAudio->PlaySFX("SFX/PlayerExplosion.wav");
	mWasHit = true;
	mInvincible = true;
}

void Player::Render() {

	if (Active())
	{
		if (mVisible) {
			if (mAnimating) {
				mDeathAnimation->Render();
			}
			else {
				mShip->Render();
			}
		}
	}
	
	PhysEntity::Render(); 
	
	for (int i = 0; i < MAX_MISSILES; ++i) {
		mFmissiles[i]->Render();
	}
}

void Player::Update() {
	if (mAnimating) {

		if (mWasHit) {
			this->Position(Graphics::SCREEN_HEIGHT / 2, Graphics::SCREEN_WIDTH / 2);
			mVelocity = 0.0f;
			PhysicsManager::Instance()->UnregisterEntity(mId);
			mWasHit = false;
		}

		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	}

	else {
		if (Active()) {
			HandleMovement();
			HandleFiring();		
		}
	}

	if (mInvincible)
	{
		mInvincibilityTimer += mTimer->DeltaTime();
		if (mInvincibilityTimer >= mInvincibilityTime)
		{
			mInvincible = false;
			mInvincibilityTimer = 0;
			mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);
		}
	}

	for (int i = 0; i < MAX_MISSILES; ++i) {
		mFmissiles[i]->Update();
	}

	if (Lives() <= 0)
	{
		Active(false);
	}
}

void Player::Visible(bool visible) {
	mVisible = visible;
}

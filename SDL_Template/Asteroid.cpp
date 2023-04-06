#include "Asteroid.h"

void Asteroid::HandleMovement()
{
	Position(Position() + mVelocity);

	if (Position().x > mMoveBoundsHorizontal.y)
	{
		Position(mMoveBoundsHorizontal.x, Position().y);
	}
	else if (Position().x < mMoveBoundsHorizontal.x)
	{
		Position(mMoveBoundsHorizontal.y, Position().y);
	}

	if (Position().y > mMoveBoundsVertical.y)
	{
		Position(Position().x, mMoveBoundsVertical.x);
	}
	else if (Position().y < mMoveBoundsVertical.x)
	{
		Position(Position().x, mMoveBoundsVertical.y);
	}
}

Asteroid::Asteroid()
{
	mTimer = Timer::Instance();
	mRandom = Random::Instance();

	mMoveSpeed = 5.0f;

	mVelocity.x = mRandom->RandomRange(-1.0f, 1.0f);
	mVelocity.y = mRandom->RandomRange(-1.0f, 1.0f);

	asteroidTex = new Texture("Asteroids.png", 1, 118, 13, 10);
	asteroidTex->Parent(this);
	asteroidTex->Position(Vec2_Zero);
	asteroidTex->Scale(Vector2(5, 5));

	mMoveBoundsHorizontal = Vector2(0.0f, Graphics::SCREEN_WIDTH);
	mMoveBoundsVertical = Vector2(0.0f, Graphics::SCREEN_HEIGHT);

	AddCollider(new BoxCollider(Vector2(16.0f, 67.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);
}
Asteroid::~Asteroid()
{
	asteroidTex = nullptr;
	delete asteroidTex;
}

void Asteroid::Hit(PhysEntity* other)
{
	
}

void Asteroid::Update()
{
	HandleMovement();
}
void Asteroid::Render()
{
	asteroidTex->Render();
}
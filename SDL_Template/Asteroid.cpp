#include "Asteroid.h"
#include "PlayScreen.h"

Asteroid::Asteroid(){
	mTimer = Timer::Instance();
	mRandom = Random::Instance();

	mMoveSpeed = 5.0f;

	mVelocity.x = mRandom->RandomRange(-1.0f, 1.0f);
	mVelocity.y = mRandom->RandomRange(-1.0f, 1.0f);

	mAsteroidTextRand = mRandom->RandomRange(0, 3);

	mSpritePos.push_back(1);
	mSpritePos.push_back(32);
	mSpritePos.push_back(62);
	mSpritePos.push_back(94);

	asteroidTex = new Texture("Asteroids.png", mSpritePos[mAsteroidTextRand], 90, 26, 26);
	asteroidTex->Parent(this);
	asteroidTex->Position(Vec2_Zero);
	asteroidTex->Scale(Vector2(3, 3));

	mMoveBoundsHorizontal = Vector2(0.0f, Graphics::SCREEN_WIDTH);
	mMoveBoundsVertical = Vector2(0.0f, Graphics::SCREEN_HEIGHT);

	AddCollider(new BoxCollider(Vector2(16.0f, 67.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);
}
Asteroid::Asteroid(int size, PlayScreen* playScreen)
{
	mTimer = Timer::Instance();
	mRandom = Random::Instance();

	mPlayScreen = playScreen;

	mSize = size;

	mMoveSpeed = 5.0f;

	mVelocity.x = mRandom->RandomRange(-1.0f, 1.0f);
	mVelocity.y = mRandom->RandomRange(-1.0f, 1.0f);
	
	mAsteroidTextRand = mRandom->RandomRange(0, 3);

	mSpritePos.push_back(1);
	mSpritePos.push_back(32);
	mSpritePos.push_back(62); 
	mSpritePos.push_back(94);

	asteroidTex = new Texture("Asteroids.png",mSpritePos[mAsteroidTextRand], 90, 26, 26);
	asteroidTex->Parent(this);
	asteroidTex->Position(Vec2_Zero);
	asteroidTex->Scale(Vector2(mSize + 1,mSize + 1));

	mMoveBoundsHorizontal = Vector2(0.0f, Graphics::SCREEN_WIDTH);
	mMoveBoundsVertical = Vector2(0.0f, Graphics::SCREEN_HEIGHT);

	AddCollider(new BoxCollider(Vector2(16.0f, 67.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);
}

Asteroid::~Asteroid()
{
	mTimer = nullptr;
	mRandom = nullptr;

	asteroidTex = nullptr;
	delete asteroidTex;
}

void Asteroid::HandleMovement()
{
	Position(Position() + mVelocity);

	//teleport code
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

void Asteroid::Hit(PhysEntity* other)
{
	std::cout << "I've Been Hit!";
	PhysicsManager::Instance()->UnregisterEntity(mId);
	mPlayScreen->SpawnAsteroid(mSize, Position(), this);
}

void Asteroid::Update()
{
	HandleMovement();
}
void Asteroid::Render()
{
	asteroidTex->Render();
}
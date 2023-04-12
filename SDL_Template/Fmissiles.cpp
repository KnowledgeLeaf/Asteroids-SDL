#include "Fmissiles.h"

Fmissiles::Fmissiles(){
	mTimer = Timer::Instance();
	mTexture = new Texture("Asteroids.png", 30, 60, 5, 5);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero); 
	mSpeed = 200.0f;
	
	mMoveBoundsHorizontal = Vector2(0.0f, Graphics::SCREEN_WIDTH);
	mMoveBoundsVertical = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mTexture->Scale(Vector2(3, 3));

	AddCollider( new BoxCollider(Vector2(5.0f, 5.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::FriendlyProjectiles);

	Reload();
}

Fmissiles::~Fmissiles() {
	mTimer = nullptr;
	delete mTexture;
	mTexture = nullptr;
}

void Fmissiles::Fire(Vector2 pos) {
	Position(pos);
	Active(true);
}

void Fmissiles::Reload() 
{
	Active(false);
}

void Fmissiles::Update() {
		
	if (Active()) 
	{
		Translate(-Vec2_Up * mSpeed * mTimer->DeltaTime());
		Vector2 pos = Position();
		HandleMovement();
	}
}


void Fmissiles::Render() {
	if (Active()) 
	{
		mTexture->Render();
	}
}

void Fmissiles::Hit(PhysEntity* other)
{
	if (Active())
	{
		std::cout << "MISSILE HIT!";
		Reload();
	}
}

bool Fmissiles::IgnoreCollisions()
{
	return !Active();
}

void Fmissiles::HandleMovement() {
	
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
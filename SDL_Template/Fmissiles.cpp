#include "Fmissiles.h"

Fmissiles::Fmissiles(){
	mTimer = Timer::Instance();
	mTexture = new Texture("Asteroids.png", 30, 60, 5, 5);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero); 
	
	mMoveBoundsHorizontal = Vector2(0.0f, Graphics::SCREEN_WIDTH);
	mMoveBoundsVertical = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mTexture->Scale(Vector2(3, 3));
	mSpeed = 200.0f;
}
Fmissiles::~Fmissiles() {

	delete mTexture;
	mTexture = nullptr;

}

void Fmissiles::HandleMovement() {
	Translate(-Vec2_Up * mSpeed * mTimer->DeltaTime());

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

void Fmissiles::Update() {
	HandleMovement();
}

void Fmissiles::Hit(PhysEntity* other) {
	delete(this);
}
void Fmissiles::Render() {
	mTexture->Render();
	PhysEntity::Render();
}
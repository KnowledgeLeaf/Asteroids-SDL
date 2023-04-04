#include "Asteroid.h"


void Asteroid::HandleMovement()
{

}

Asteroid::Asteroid()
{
	asteroidTex = new Texture("Asteroids.png", 1, 118, 13, 10);
	asteroidTex->Parent(this);
	asteroidTex->Position(Vec2_Zero);
	asteroidTex->Scale(Vector2(10, 10));

	mMoveBounds = Vector2(0.0f, 800.0f);

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
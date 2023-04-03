#include "Asteroid.h"


void Asteroid::HandleMovement()
{

}

Asteroid::Asteroid()
{
	asteroidTex = new Texture("PlayerShips.png", 0, 0, 60, 64);

	mMoveBounds = Vector2(0.0f, 800.0f);
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
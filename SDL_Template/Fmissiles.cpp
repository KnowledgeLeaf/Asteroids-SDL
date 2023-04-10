#include "Fmissiles.h"

Fmissiles::Fmissiles(){


	mTexture = new Texture("Asteroids.png", 0, 50, 13, 15);
	

}
Fmissiles::~Fmissiles() {

	delete mTexture;
	mTimer = nullptr;

}

void Fmissiles::HandleMovement() {


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
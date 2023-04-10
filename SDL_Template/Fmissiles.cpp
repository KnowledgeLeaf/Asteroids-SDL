#include "Fmissiles.h"

Fmissiles::Fmissiles(){


	mTexture = new Texture("Asteroids.png", 40, 62, 20, 20);
	

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
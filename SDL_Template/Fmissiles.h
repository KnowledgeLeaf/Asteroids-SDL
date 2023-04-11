#ifndef __Fmissiles_H
#define __Fmissiles_H

#include "Texture.h"
#include "Timer.h"
#include "PhysEntity.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

using namespace SDLFramework;

class Fmissiles : public PhysEntity {

private:
	Timer* mTimer;
	Texture* mTexture; 
	float mSpeed;
	
	void HandleMovement();
	Vector2 mMoveBoundsHorizontal;
	Vector2 mMoveBoundsVertical;

public:
	Fmissiles();
	~Fmissiles();

	void Fire(Vector2 pos);	
	void Reload();

	void Hit(PhysEntity* other) override;

	void Update() override;
	void Render() override;
}; 

#endif 
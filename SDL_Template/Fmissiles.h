#ifndef __Fmissiles_H
#define __Fmissiles_H
#include "PhysEntity.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "AnimatedTexture.h"
#include "Timer.h"

using namespace SDLFramework;

class Fmissiles :public PhysEntity {

private:
	Timer* mTimer;
	float mSpeed;
	Vector2 mMoveBoundsHorizontal;
	Vector2 mMoveBoundsVertical;
	void HandleMovement();
	Texture* mTexture;

public:
	Fmissiles();
	~Fmissiles();
	void Hit(PhysEntity* other) override;
	void Update() override;
	void Render() override;

};

#endif 
#include "PhysEntity.h"
#include "Random.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

using namespace SDLFramework;

class Asteroid : public PhysEntity
{
private:

	Texture* asteroidTex;

	float mMoveSpeed;
	Vector2 mMoveDirection;
	Vector2 mMoveBounds;

	void HandleMovement();

public:
	Asteroid();
	~Asteroid();

	void Hit(PhysEntity* other) override;

	void Update() override;
	void Render() override;
};
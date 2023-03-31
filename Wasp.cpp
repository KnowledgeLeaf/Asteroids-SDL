#include "Wasp.h"

std::vector<std::vector<Vector2>> Wasp::sDivePaths;

void Wasp::FlyInComplete() {
	if (mDiver) {
		mCurrentState = Dead;
	}
	else {
		JoinFormation();
	}
}

void Wasp::CreateDivePaths() {
	int currentPath = 0;
	BezierPath* path = new BezierPath();

	path->AddCurve({
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, -45.0f),
		Vector2(-60.0f, -45.0f),
		Vector2(-60.f, 0.0f) }, 15);
	path->AddCurve({
		Vector2(-60.0f, 0.0f),
		Vector2(-60.0f, 80.0f),
		Vector2(0.0f, 150.0f),
		Vector2(100.0f, 150.0f) }, 15);
	path->AddCurve({
		Vector2(100.0f, 150.0f),
		Vector2(250.0f, 150.0f),
		Vector2(350.0f, 200.0f),
		Vector2(350.0f, 350.0f) }, 15);
	path->AddCurve({
		Vector2(350.0f, 350.0f),
		Vector2(350.0f, 575.0f),
		Vector2(100.0f, 575.0f),
		Vector2(100.0f, 350.0f) }, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);

	delete path;
	currentPath = 1;
	path = new BezierPath();

	path->AddCurve({
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, -45.0f),
		Vector2(60.0f, -45.0f),
		Vector2(60.f, 0.0f) }, 15);
	path->AddCurve({
		Vector2(60.0f, 0.0f),
		Vector2(60.0f, 80.0f),
		Vector2(0.0f, 150.0f),
		Vector2(-100.0f, 150.0f) }, 15);
	path->AddCurve({
		Vector2(-100.0f, 150.0f),
		Vector2(-250.0f, 150.0f),
		Vector2(-350.0f, 200.0f),
		Vector2(-350.0f, 350.0f) }, 15);
	path->AddCurve({
		Vector2(-350.0f, 350.0f),
		Vector2(-350.0f, 575.0f),
		Vector2(-100.0f, 575.0f),
		Vector2(-100.0f, 350.0f) }, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;
}

Vector2 Wasp::LocalFormationPosition() {
	Vector2 retVal;
	int dir = mIndex % 2 == 0 ? -1 : 1;
	retVal.x =
		(sFormation->GridSize().x + sFormation->GridSize().x * 2 * (mIndex / 4)) *
		(float)dir;
	retVal.y =
		sFormation->GridSize().y * 2 + sFormation->GridSize().y * ((mIndex % 4) / 2);
	return retVal;
}

void Wasp::HandleDiveState() {
	int currentPath = mIndex % 2;
	if (mCurrentWaypoint < sDivePaths[currentPath].size()) {
		// follow dive path
		Vector2 waypointPos = mDiveStartPosition +
			sDivePaths[currentPath][mCurrentWaypoint];
		Vector2 dist = waypointPos - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if ((waypointPos - Position()).MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			mCurrentWaypoint += 1;
		}
	}
	else {
		// return to formation
		Vector2 dist = WorldFormationPosition() - Position();
		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			JoinFormation();
		}
	}
}

void Wasp::HandleDeadState() { }

void Wasp::RenderDiveState() {
	mTexture->Render();
	// debug render of dive path
	int currentPath = mIndex % 2;
	for (int i = 0; i < sDivePaths[0].size() - 1; i++) {
		GraphicsManager::Instance()->DrawLine(
			mDiveStartPosition.x + sDivePaths[currentPath][i].x,
			mDiveStartPosition.y + sDivePaths[currentPath][i].y,
			mDiveStartPosition.x + sDivePaths[currentPath][i + 1].x,
			mDiveStartPosition.y + sDivePaths[currentPath][i + 1].y);
	}
	// debug render of return path
	Vector2 finalPos = WorldFormationPosition();
	Vector2 pathEndPos = mDiveStartPosition +
		sDivePaths[currentPath][sDivePaths[currentPath].size() - 1];
	GraphicsManager::Instance()->DrawLine(
		pathEndPos.x,
		pathEndPos.y,
		finalPos.x,
		finalPos.y);
}

void Wasp::RenderDeadState() { }

Wasp::Wasp(int path, int index, bool challenge, bool diver)
	: Enemy(path, index, challenge), mDiver(diver) {

	mTexture = new Texture("AnimatedEnemies.png", 0, 40, 52, 40);

	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);
	mType = Enemy::Wasp;
}
Wasp::~Wasp() { }
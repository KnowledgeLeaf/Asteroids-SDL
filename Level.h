#ifndef __LEVEL_H
#define __LEVEL_H
#include "PlaySideBar.h"
#include "BackgroundStars.h"
#include "Player.h"
#include "Butterfly.h"
#include "Wasp.h"

class Level : public GameEntity {
public:
    enum LevelStates { Running, Finished, GameOver };

private:
    Timer* mTimer;
    PlaySideBar* mSideBar;
    BackgroundStars* mStars;
    int mStage;
    bool mStageStarted;
    float mLabelTimer;
    Texture* mStageLabel;
    Scoreboard* mStageNumber;
    float mStageLabelOnScreen;
    float mStageLabelOffScreen;
    Texture* mReadyLabel;
    float mReadyLabelOnScreen;
    float mReadyLabelOffScreen;
    void StartStage();

    Player* mPlayer;

    bool mPlayerHit;
    float mRespawnDelay;
    float mRespawnTimer;
    float mRespawnLabelOnScreen;
    Texture* mGameOverLabel;
    float mGameOverDelay;
    float mGameOverTimer;
    float mGameOverLabelOnScreen;

    LevelStates mCurrentState;
    Formation* mFormation;

    const int MAX_BUTTERFLIES = 16;
    int mButterflyCount;

    const int MAX_WASPS = 20;
    int mWaspCount;

    std::vector<Enemy*> mEnemies;

    void HandleStartLabels();
    void HandleCollisions();
    void HandlePlayerDeath();

    void HandleEnemySpawning();
    void HandleEnemyFormation();
    void HandleEnemyDiving();

public:
    Level(int stage, PlaySideBar* sideBar, Player* player);
    ~Level();

    LevelStates State();

    void Update() override;
    void Render() override;
};
#endif
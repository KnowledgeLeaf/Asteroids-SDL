#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H
#include "Texture.h"
#include <vector>

using namespace SDLFramework;

class Scoreboard : public GameEntity {
private:
	std::vector<Texture *> mScore;

	SDL_Color mColor;
	int mSize;

public:
	Scoreboard(int size);
	Scoreboard(SDL_Color color, int size);
	~Scoreboard();

	void Score(int score);

	void Render() override;

private:
	void ClearBoard();
};
#endif
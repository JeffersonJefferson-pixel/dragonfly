#include "GameOver.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "GameManager.h"

GameOver::GameOver() {
	setType("GameOver");
	if (setSprite("gameover") == 0)
		time_to_live = getAnimation().getSprite()->getFrameCount() *
			getAnimation().getSprite()->getSlowdown();
	else
		time_to_live = 0;

	setLocation(df::CENTER_CENTER);

	registerInterest(df::STEP_EVENT);
}

int GameOver::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}

void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}

GameOver::~GameOver() {
	GM.setGameOver();
}

int GameOver::draw() {
	return df::Object::draw();
}
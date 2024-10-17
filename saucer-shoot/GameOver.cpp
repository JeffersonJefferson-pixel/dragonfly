#include "GameOver.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "GameStart.h"

GameOver::GameOver() {
	setType("GameOver");
	// set time to live.
	if (setSprite("gameover") == 0)
		time_to_live = getAnimation().getSprite()->getFrameCount() *
			getAnimation().getSprite()->getSlowdown();
	else
		time_to_live = 0;

	setLocation(df::CENTER_CENTER);

	registerInterest(df::STEP_EVENT);
	// play gameover sound.
	df::Sound* p_sound = RM.getSound("gameover");
	if (p_sound)
		p_sound->play();
}

int GameOver::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}

void GameOver::step() {
	// decrease time to live.
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}

GameOver::~GameOver() {
	// remove saucers and view objects, re-activate gamestart.
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) {
		df::Object* p_o = i.currentObject();
		if (p_o->getType() == "Saucer" || p_o->getType() == "ViewObject")
			WM.markForDelete(p_o);
		if (p_o->getType() == "GameStart") {
			p_o->setActive(true);
			dynamic_cast <GameStart*> (p_o)->playMusic();
		}
	}
}

int GameOver::draw() {
	return df::Object::draw();
}
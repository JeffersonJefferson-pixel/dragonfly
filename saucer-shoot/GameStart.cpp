#include "GameStart.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "Hero.h"
#include "Saucer.h"
#include "Points.h"

GameStart::GameStart() {
	setType("GameStart");
	setLocation(df::CENTER_CENTER);
	setSprite("gamestart");
	registerInterest(df::KEYBOARD_EVENT);
}

int GameStart::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*) p_e;
		switch (p_keyboard_event->getKey()) {
		case df::Keyboard::P:
			start();
			break;
		case df::Keyboard::Q:
			GM.setGameOver();
			break;
		default:
			break;
		}
		return 1;
	}
	return 0;
}

void GameStart::start() {
	// add hero to world.
	new Hero;
	// add saucer to world.
	for (int i = 0; i < 16; i++) {
		new Saucer;
	}
	// set up heads-up display
	new Points;
	df::ViewObject* p_vo = new df::ViewObject;
	p_vo->setLocation(df::TOP_LEFT);
	p_vo->setViewString("Nukes");
	p_vo->setValue(1);
	p_vo->setColor(df::YELLOW);
	// when game start, become inactive.
	setActive(false);
}

int GameStart::draw() {
	return df::Object::draw();
}
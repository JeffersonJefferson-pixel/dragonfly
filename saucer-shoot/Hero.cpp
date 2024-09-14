#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventStep.h"
#include "EventMouse.h"

#include "Hero.h"

Hero::Hero() {
	move_slowdown = 2;
	move_countdown = move_slowdown;
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;

	// Link to "ship" sprite.
	setSprite("ship");
	// register interested event.
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MSE_EVENT);
	
	setType("Hero");
	// set position on the left edge of the window, mid-way down vertically.
	df::Vector p(7, WM.getBoundary().getVertical() / 2);
	setPosition(p);
}

int Hero::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast<const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		return 1;
	}
	return 0;
}


void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {
	switch (p_keyboard_event->getKey()) {
		// quit
		case df::Keyboard::Q: 
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
				GM.setGameOver();
			}
			break;
		// up
		case df::Keyboard::W:
			if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
				move(-1);
			}
			break;
		case df::Keyboard::S:
			if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
				move(+1);
			}
			break;
	}
}

void Hero::move(int dy) {
	// see if time to move.
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	// if statys on window, allow move
	df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
	if ((new_pos.getY() > 3) && (new_pos.getY() < WM.getBoundary().getVertical() - 1))
		WM.moveObject(this, new_pos);
}

void Hero::step() {
	// move countdown
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;
	// fire countdown
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
}

void Hero::fire(df::Vector target) {
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;
	// fire bullet towards target.
	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);
	Bullet* p = new Bullet(getPosition());
	p->setVelocity(v);
}

void Hero::mouse(const df::EventMouse* p_mouse_event) {
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::LEFT))
		fire(p_mouse_event->getMousePosition());
}
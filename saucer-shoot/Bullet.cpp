#include "WorldManager.h"
#include "EventOut.h";

#include "Bullet.h"

Bullet::Bullet(df::Vector hero_pos) {
	// link to bullet sprite.
	setSprite("bullet");
	// set type.
	setType("Bullet");
	// set stating location, based on hero's position.
	df::Vector p(hero_pos.getX() + 3, hero_pos.getY());
	setPosition(p);
	// bullets move 1 space each game loop.
	// the direction is set when the hero fires.
	setSpeed(1);
	// make bullet soft to pass through hero.
	setSolidness(df::SOFT);
}

int Bullet::eventHandler(const df::Event* p_e) {
	// react when bullet is leaves the window.
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	// react when it hits a saucer
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
			hit(p_collision_event);
		return 1;
	}
	return 0;
}

void Bullet::out() {
	// mark self for deletion.
	WM.markForDelete(this);
}

void Bullet::hit(const df::EventCollision *p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "Saucer") ||
		(p_collision_event -> getObject2() -> getType() == "Saucer")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}
}
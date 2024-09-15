#include "Saucer.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "stdlib.h"
#include "Explosion.h"
#include "EventView.h"
#include "EventNuke.h"
#include "Points.h"

Saucer::Saucer() {
	// Setup "saucer" sprite.
	setSprite("saucer");

	// Set object type.
	setType("Saucer");
	// register event of interest.
	registerInterest(NUKE_EVENT);

	// Set speed in horizontal direction.
	setVelocity(df::Vector(-0.25, 0)); /// 1 space left ever for frames.

	// Move saucer to the start of the screen.
	moveToStart();
}

Saucer::~Saucer() {
	// send view event with points to viewobjects.
	df::EventView ev(POINTS_STRING, 10, true);
	WM.onEvent(&ev);
}

int Saucer::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c = dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_c);
		return 1;
	}
	if (p_e->getType() == NUKE_EVENT) {
		destroy();
	}

	return 0;
}

void Saucer::out() {
	if (getPosition().getX() >= 0)
		return;
	moveToStart();
	// spawn new saucer to make game harder.
	new Saucer;
}

void Saucer::moveToStart() {
	df::Vector temp_pos;

	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

	// x is off right side of window
	temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f);

	// y is in verifical range
	temp_pos.setY(rand() % (int)(world_vert - 1) + 1.0f);

	// if collosion, move right slightly until empty space.
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (!collision_list.isEmpty()) {
		temp_pos.setX(temp_pos.getX() + 1);
		collision_list = WM.getCollisions(this, temp_pos);
	}

	WM.moveObject(this, temp_pos);
}

void Saucer::hit(const df::EventCollision* p_collision_event) {
	// ignore saucer-saucer collision.
	if ((p_collision_event->getObject1()->getType() == "Saucer") &&
		(p_collision_event->getObject2()->getType() == "Saucer"))
		return;
	// create explosion if saucer-bullet.
	if ((p_collision_event->getObject1()->getType() == "Bullet") ||
		(p_collision_event->getObject2()->getType() == "Bullet")) {
		destroy();
	}
	// hero-saucer collision.
	if ((p_collision_event->getObject1()->getType() == "Hero") ||
		(p_collision_event->getObject2()->getType() == "Hero")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}
}

void Saucer::destroy() {
	Explosion* p_explosion = new Explosion();
	p_explosion->setPosition(this->getPosition());

	// mark for deletion.
	WM.markForDelete(this);

	// spawn new saucer.
	new Saucer;
}
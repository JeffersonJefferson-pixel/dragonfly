#include "Saucer.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "stdlib.h"
#include "Explosion.h"

Saucer::Saucer() {
	// Setup "saucer" sprite.
	setSprite("saucer");

	// Set object type.
	setType("Saucer");

	// Set speed in horizontal direction.
	setVelocity(df::Vector(-0.25, 0)); /// 1 space left ever for frames.

	// Set starting location in the middle of window.
	int world_horiz = (int) WM.getBoundary().getHorizontal();
	int world_vert = (int)WM.getBoundary().getVertical();
	df::Vector p(world_horiz / 2, world_vert / 2);
	setPosition(p);
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

	return 0;
}

void Saucer::out() {
	if (getPosition().getX() >= 0)
		return;
	moveToStart();
}

void Saucer::moveToStart() {
	df::Vector temp_pos;

	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

	// x is off right side of window
	temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f);

	// y is in verifical range
	temp_pos.setY(rand() % (int)(world_vert - 1) + 1.0f);

	WM.moveObject(this, temp_pos);
}

void Saucer::hit(const df::EventCollision* p_c) {
	// ignore saucer-saucer collision.
	if ((p_c->getObject1()->getType() == "Saucer") &&
		(p_c->getObject2()->getType() == "Saucer"))
		return;
	// create explosion if saucer-bullet.
	if ((p_c->getObject1()->getType() == "Bullet") ||
		(p_c->getObject2()->getType() == "Bullet")) {
		Explosion *p_explosion = new Explosion();
		p_explosion->setPosition(this->getPosition());

		// set to spectral
		setSolidness(df::SPECTRAL);
		
		// spawn new saucer.
		new Saucer();
	}
}
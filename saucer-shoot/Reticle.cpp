#include "EventMouse.h"
#include "DisplayManager.h"
#include "WorldManager.h"

#include "Reticle.h"

Reticle::Reticle() {
	setType("Reticle");
	// should not collide with other objects.
	setSolidness(df::SPECTRAL);
	// draw in foreground.
	setAltitude(df::MAX_ALTITUDE);
	// register event of interest.
	registerInterest(df::MSE_EVENT);
	// start in middle of window.
	df::Vector p(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2);
	setPosition(p);
}

int Reticle::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
		if (p_mouse_event->getMouseAction() == df::MOVED) {
			// change location to new mouse position.
			setPosition(p_mouse_event->getMousePosition());
			return 1;
		}
	}
	return 0;
}

int Reticle::draw() {
	return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}
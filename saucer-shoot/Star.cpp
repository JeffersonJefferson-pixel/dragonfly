
#include <stdlib.h>

#include "Star.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "DisplayManager.h"

Star::Star() {
	setType("Star");
	setSolidness(df::SPECTRAL);
	// random velocity.
	setVelocity(df::Vector((float)-1.0 / (rand() % 10 + 1), 0));

	setAltitude(0);

	// rnadom position.
	df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
		(float)(rand() % (int)WM.getBoundary().getVertical()));
	setPosition(p);

	// draw star with circle.
	// closer stars are bigger and move faster.
	df::Shape s;
	s.setColor(df::WHITE);
	s.setType(df::CIRCLE);
	s.setSize(5 * getVelocity().getMagnitude());
	setShape(s);
}

int Star::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
}

void Star::out() {
	// move star back to a random position the right of the window.
	df::Vector p((float)(WM.getBoundary().getHorizontal() + rand() % 20),
		(float)(rand() % (int)WM.getBoundary().getVertical()));

	setPosition(p);
	setVelocity(df::Vector(-1.0 / (rand() % 10 + 1), 0));

	df::Shape s;
	s.setColor(df::WHITE);
	s.setType(df::CIRCLE);
	s.setSize(5 * getVelocity().getMagnitude());
	setShape(s);
}
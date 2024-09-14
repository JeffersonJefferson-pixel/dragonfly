#include "EventStep.h"
#include "WorldManager.h"

#include "Explosion.h"

Explosion::Explosion() {
	// link to explosion sprite.
	if (setSprite("explosion") == 0)
		// set live time
		time_to_live = getAnimation().getSprite()->getFrameCount();
	else
		time_to_live = 0;
	// set solidness
	setSolidness(df::SPECTRAL);
	// register event of interest.
	registerInterest(df::STEP_EVENT);
}

int Explosion::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}

void Explosion::step() {
	// reduce time to live
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}
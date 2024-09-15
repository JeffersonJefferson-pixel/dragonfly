#include "EventStep.h"

#include "Points.h"

Points::Points() {
	setLocation(df::TOP_RIGHT);
	setViewString(POINTS_STRING);
	setColor(df::YELLOW);

	registerInterest(df::STEP_EVENT);
}

int Points::eventHandler(const df::Event *p_e) {
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_step = dynamic_cast<const df::EventStep*> (p_e);
		if (p_step->getStepCount() % 30 == 0)
			setValue(getValue() + 1);
	}
	
	return 0;
}

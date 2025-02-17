#include "Object.h"

#define STAR_CHAR '.'

class Star : public df::Object {
private:
	// handle out event.
	void out();

public:
	Star();
	int eventHandler(const df::Event* p_e) override;
};
#include "Object.h"

class Saucer : public df::Object {
	public: 
		Saucer();
		int eventHandler(const df::Event* p_e) override;
		void Saucer::out();
		void Saucer::moveToStart();
};
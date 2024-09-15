#include "Object.h"
#include "EventCollision.h"

class Saucer : public df::Object {
	private: 
		// handle saucer collision event.
		void hit(const df::EventCollision* p_c);
		// handle when saucer moves out if the screen.
		void Saucer::out();
		// moves saucer to the right of the screen.
		void Saucer::moveToStart();
		void destroy();
	public: 
		Saucer();
		~Saucer();
		int eventHandler(const df::Event* p_e) override;
};
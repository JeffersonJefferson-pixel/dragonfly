#include "Object.h"
#include "EventKeyboard.h"

class Hero : public df::Object {
	private: 
		int move_slowdown;
		int move_countdown;

		void kbd(const df::EventKeyboard* p_keyboard_event);
		void move(int dy);
		void step();
	
	public:
		Hero();
		int eventHandler(const df::Event* p_e) override;
};
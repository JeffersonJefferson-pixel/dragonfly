#include "Object.h"
#include "EventKeyboard.h"

#include "Bullet.h"

class Hero : public df::Object {
	private: 
		int move_slowdown;
		int move_countdown;
		int fire_slowdown;
		int fire_countdown;

		void kbd(const df::EventKeyboard* p_keyboard_event);
		void move(int dy);
		// decrement coundown.
		void step();
		// create bullet aimed at target.
		void fire(df::Vector target);
		// handle mouse event.
		void mouse(const df::EventMouse* p_mouse_event);
	
	public:
		Hero();
		int eventHandler(const df::Event* p_e) override;
};
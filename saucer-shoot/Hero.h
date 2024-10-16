#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

#include "Bullet.h"
#include "Reticle.h"


class Hero : public df::Object {
	private: 
		int move_slowdown;
		int move_countdown;
		int fire_slowdown;
		int fire_countdown;
		Reticle* p_reticle;
		int nuke_count;

		void kbd(const df::EventKeyboard* p_keyboard_event);
		void move(int dy);
		// decrement coundown.
		void step();
		// create bullet aimed at target.
		void fire(df::Vector target);
		// handle mouse event.
		void mouse(const df::EventMouse* p_mouse_event);
		// create a nuke event.
		void nuke();
	
	public:
		Hero();
		~Hero();
		int eventHandler(const df::Event* p_e) override;
};
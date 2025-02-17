#include <string>

namespace df {
	class Manager {
	private:
		std::string m_type;	// manager type.
		bool m_is_started;	// true when manager is started.
	protected:
		// set manager type.
		void setType(std::string type);
	public:
		Manager();
		virtual ~Manager();

		// get type of manager.
		std::string getType() const;

		// start manager.
		virtual int startUp();

		// shutdown manager.
		virtual void shutDown();

		// return true when manager is started.
		bool isStarted() const;
	};
}
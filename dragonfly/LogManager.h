#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

#include <stdio.h>

#include "Manager.h"

namespace df {
	const std::string LOGFILE_NAME = "dragonfly.log";

	class LogManager : public Manager {
	private:
		LogManager();
		LogManager(LogManager const&);
		void operator=(LogManager const&);
		bool m_do_flush; // true if flush to disk after each write.
		FILE* m_p_f; // pointer to logfile struct.

	public:
		~LogManager();

		// get the one and only instance of log manager.
		static LogManager& getInstance();

		// start log manager.
		int startUp();

		// shut down log manager.
		void shutDown();

		void setFlush(bool do_flush = true);

		// write to logfile.
		int writeLog(const char* fmt, ...) const;
	};
}

#endif
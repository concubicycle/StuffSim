#ifndef SS_OS_H
#define SS_OS_H

#include <memory>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <mutex>
#include <functional>

#include "system_header.h"
#include "ss_string_util.h"

namespace StuffSim
{
	class StuffSimOS
	{
	public:
		StuffSimOS(const StuffSimOS& orig);
		StuffSimOS();
		~StuffSimOS();

		/*
			In the future, we may well need a stream so we can direct stdio
			to whatever streams we pass in. This will allow greater flexibility, 
			but for now just do this..
		*/
		enum StdIOTarget
		{
			Console
		};

		void setStdIOTarget(StdIOTarget newTarget);

		void openConsole();
		void closeConsole();

		static std::string getLastError();

	private:
		struct OSStateImpl;
		std::unique_ptr<OSStateImpl> m_osState;
		std::mutex m_osStateMutex;

		StdIOTarget m_currentIOTarget;
		
		bool m_isConsoleOpen;
		
		std::function<void()> m_onConsoleReady; //TODO: When delegates are implemented, use an internal event here. 

		void redirectIOToConsole();
	};
}

#endif

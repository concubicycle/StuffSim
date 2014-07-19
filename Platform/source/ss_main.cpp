/*
	This is the entry point for the StuffSim engine exe. 
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "ss_os.h"
#include "ss_main.h"

using namespace StuffSim;

StuffSimExitStatus startStuffSim()
{	
	StuffSimOS os;
	os.setStdIOTarget(StuffSimOS::StdIOTarget::Console);

	os.openConsole();

	std::cout << "Hello engine!" << std::endl;

	getchar();
	return StuffSimExitStatus::OK;
}

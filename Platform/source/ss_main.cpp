/*
	This is the entry point for the StuffSim engine exe. 
*/

#include <stdio.h>
#include <string>
#include "ss_main.h"


#include "os_tests.h"
#include "path_tests.h"

#include "ss_iostream.h"

using StuffSim::StuffSimOS;


StuffSimExitStatus startStuffSim()
{
	StuffSimOS os;
	os.setStdIOTarget(StuffSimOS::StdIOTarget::Console);
	os.openConsole();

	run_os_tests(os);

	std::cout << std::endl << std::endl;

	run_path_tests();

	getchar();	
	return StuffSimExitStatus::OK;
}

#include "os_tests.h"

using namespace StuffSim;

void run_os_tests(StuffSimOS& os)
{
	
	os.setStdIOTarget(StuffSimOS::StdIOTarget::Console);

	os.openConsole();

	std::this_thread::sleep_for(std::chrono::seconds(1));

	os.closeConsole();

	std::this_thread::sleep_for(std::chrono::milliseconds(400));

	os.openConsole();

	std::cout << os.getLastError() << std::endl;

	std::cout << "######## OS TEST ############" << std::endl;

	std::cout << "Hello engine!" << std::endl;	
}
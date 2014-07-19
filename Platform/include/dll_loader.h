#ifndef SS_DLL_LOADER_H
#define SS_DLL_LOADER_H

#include <cstdint>
#include <memory>
#include <string>
#include "system_header.h"

namespace StuffSim
{
	class SharedLibraryLoader
	{
	public:
		enum LoadStatus : std::int8_t
		{
			Success = 0,
			Failure = 1
		};

		//Constructor and destructor
		SharedLibraryLoader();
		~SharedLibraryLoader();

		OSString getLoadStatus();
		

	private:
		struct OSSpecificStateImpl; //holds platform specific state in cpp files
		
		std::unique_ptr<OSSpecificStateImpl> m_osSpecificState;
		LoadStatus m_lastLoadStatus;
	};
}

#endif

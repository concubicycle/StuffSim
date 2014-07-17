#ifndef SS_DLL_LOADER
#define SS_DLL_LOADER

#include "system_header.h"
#include <cstdint>
#include <memory>
#include <string>

using std::string;

namespace StuffSimPlatform
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

		string getLoadStatus();
		

	private:
		struct OSSpecificStateImpl; //holds platform specific state in cpp files
		
		std::unique_ptr<OSSpecificStateImpl> m_osSpecificState;
		LoadStatus m_lastLoadStatus;
	};
}

#endif

#include "dll_loader.h"

using namespace StuffSim;

struct SharedLibraryLoader::OSSpecificStateImpl
{
	DWORD postLoadError;	
	HINSTANCE loadedInstance;
};


SharedLibraryLoader::SharedLibraryLoader()
{

}


SharedLibraryLoader::~SharedLibraryLoader()
{

}


OSString SharedLibraryLoader::getLoadStatus()
{
	if (m_lastLoadStatus == LoadStatus::Failure)
	{
		LPVOID lpMsgBuf;
		DWORD bufLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			m_osSpecificState->postLoadError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

		if (bufLen)
		{
			LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
			OSString result(lpMsgStr, lpMsgStr + bufLen);
			LocalFree(lpMsgBuf);
			return result;
		}
		else
		{
			//TODO: Use logger here
			return SS_STR_LIT("Failed to obtain status.");
		}
	}
	
	return SS_STR_LIT("Success");
}


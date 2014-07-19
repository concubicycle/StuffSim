#include "path.h"
using namespace StuffSim;

//define 
struct Path::OSSpecificStateImpl
{
	const OSString volumePathDivider = SS_STR_LIT(":\\");
	const OSChar dirDivider = '\\';
};


Path::Path(OSString path)
{
	initWithString(path);
}

Path::Path(const Path& path) : m_osSpecificState(new OSSpecificStateImpl)
{
	initWithString(path.m_fullPath);

	//set members of m_osSpecificState here.
}

Path::~Path() 
{

}

void Path::initWithString(OSString path)
{
	if (path.empty())
	{
		//TODO: log error!
		return;
	}

	StuffSim::trim(path);

	//if a drive is specified, it's a full path
	size_t indexOfVolPathDivider = path.find(m_osSpecificState->volumePathDivider);
	if (indexOfVolPathDivider != OSString::npos)
	{
		m_drive = path[0];
		m_pathString = path.substr(3, path.length() - 2);
	}
	else
	{
		m_drive = SS_STR_LIT("");
		m_pathString = path;
	}
}



Path Path::pathDir()
{
	size_t indexOfLastSlash = m_fullPath.find_last_of(m_osSpecificState->dirDivider);
	if (indexOfLastSlash == OSString::npos)
	{
		return Path(m_fullPath);
	}

	return Path(m_fullPath.substr(0, indexOfLastSlash+1));
}

bool Path::isValid()
{
	return true;
}

std::uint32_t Path::getSize()
{
	return 0;
}

bool Path::isFile()
{
	return true;
}

bool Path::isDir()
{
	return true;
}

const OSString Path::getExecutablePath()
{
	if (m_executablePath.empty())
	{
		OSChar pathBuffer[_MAX_PATH];
		int pathLen = GetModuleFileNameW(NULL, pathBuffer, _MAX_PATH);
		m_executablePath = OSString(pathBuffer);

		
		if (pathLen == 0)
		{
			//TODO: log error
		}
	}
	
	return m_executablePath;
}

OSString StuffSim::Path::m_executablePath;

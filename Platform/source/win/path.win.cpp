#include "path.h"
using namespace StuffSumPlatform;

#define VOLUME_PATH_DIVIDER ":\\"
#define DIR_DIVIDER '\\'

struct Path::OSSpecificStateImpl
{

};

Path::Path(std::string path)
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

void Path::initWithString(const std::string& path)
{
	if (path.empty())
	{
		//TODO: log error!
		return;
	}

	std::string trimmedPath = path;
	trim(trimmedPath);

	//if a drive is specified, it's a full path
	size_t indexOfVolPathDivider = trimmedPath.find(VOLUME_PATH_DIVIDER);
	if (indexOfVolPathDivider != std::string::npos)
	{
		m_drive = trimmedPath[0];
		m_pathString = trimmedPath.substr(3, trimmedPath.length() - 3);
	}
	else
	{
		m_drive = "";
		m_pathString = trimmedPath;
	}
}



Path Path::pathDir()
{
	size_t indexOfLastSlash = m_fullPath.find_last_of(DIR_DIVIDER);
	if (indexOfLastSlash == std::string::npos)
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

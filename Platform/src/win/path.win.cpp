#include "path.h"
using namespace StuffSumPlatform;

#define VOLUME_PATH_DIVIDER ":\\"
#define DIR_DIVIDER '\\'

struct Path::OSSpecificStateImpl
{

};

Path::Path(std::string path)
{
	path = trim(path);

	//if a drive is specified, it's a full path
	size_t indexOfVolPathDivider = path.find(VOLUME_PATH_DIVIDER);
	if (indexOfVolPathDivider != std::string::npos)
	{
		m_drive = path[0];
		m_pathString = path.substr(3, path.length() - 3);
	}
	else
	{
		m_drive = "";
		m_pathString = path;
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

}

std::uint32_t Path::getSize()
{

}

bool Path::isFile()
{

}

bool Path::isDir()
{

}

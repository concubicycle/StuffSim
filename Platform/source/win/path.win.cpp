/*
	TODO: A bunch of 'new' operators.. see if you can get an allocator in here
*/

#include "path.h"

#pragma comment(lib, "Shlwapi.lib")

using namespace StuffSim;


//structures and classes
struct Path::OSSpecificStateImpl
{
	static const OSString m_volumePathDivider;
	static const OSChar m_dirDivider;
	static const OSChar m_rootOfCurrentDisk;
	
	OSSpecificStateImpl() {} //default
	OSSpecificStateImpl(const OSSpecificStateImpl& other) { }
};


//constructors
Path::Path() : m_osSpecificState(new OSSpecificStateImpl), m_valid(false), m_drive(0) { } //default

Path::Path(OSString path) : m_osSpecificState(new OSSpecificStateImpl)
{
	initWithString(path);
}

Path::Path(const Path& path) //copy
	: m_osSpecificState(new OSSpecificStateImpl(*(path.m_osSpecificState)))
	, m_valid(path.m_valid)
	, m_drive(path.m_drive)
	, m_fullPath(path.m_fullPath)
	, m_full(path.m_full) { }


//destructors
Path::~Path() 
{

}


//public functions

void Path::makeFullyResolved()
{
	if (m_drive != 0)
		return;

	m_fullPath = getExecutablePath().appendPathStr(m_fullPath);
	initWithString(m_fullPath);
}


void Path::normalize()
{
	OSChar buffer[MAX_PATH];
	bool success = PathCanonicalizeW(buffer, getFullPathStr().c_str()) != 0;

	if (success)
		initWithString(buffer);
	else
	{
		//TODO: log error
	}
}


Path Path::getExecutablePath()
{
	return s_executablePath;
}


Path Path::pathDir() const
{
	return Path(pathDirStr());
}


OSString Path::pathDirStr() const
{
	size_t indexOfLastSlash = m_fullPath.find_last_of(OSSpecificStateImpl::m_dirDivider);

	if (indexOfLastSlash == OSString::npos || indexOfLastSlash == m_fullPath.length() - 1)
		return m_fullPath;
	
	return m_fullPath.substr(0, indexOfLastSlash + 1);
}


bool Path::isValid() const
{
	return PathFileExistsW(getFullPathStr().c_str()) != 0;
}


const OSString& Path::getFullPathStr() const 
{
	return m_fullPath;
}


//operators
Path& StuffSim::Path::operator=(const Path& other)
{
	if (this != &other)
	{
		this->m_osSpecificState.reset(new OSSpecificStateImpl(*(other.m_osSpecificState)));
		m_valid = other.m_valid;
		m_fullPath = other.m_fullPath;
		m_drive = other.m_drive;
		m_fullPath = other.m_fullPath;
	}
	return *this;
}


Path Path::operator+(const Path& otherPath) const
{
	return  (*this) + otherPath.m_fullPath;
}


Path Path::operator+(const OSString& otherPathString) const
{
	bool thisHasSlash = m_fullPath.back() == OSSpecificStateImpl::m_dirDivider;
	bool otherHasSlash = otherPathString.front() == OSSpecificStateImpl::m_dirDivider;

	//try to concatenate the paths, assuming that the end of this path is actually a directory
	return Path(appendPathStr(otherPathString));
}


//private
Path Path::initExecutablePath()
{
	//set the executable path
	OSChar pathBuffer[_MAX_PATH];
	int pathLen = GetModuleFileNameW(NULL, pathBuffer, _MAX_PATH);

	if (pathLen == 0)
	{
		//TODO: log error
		return Path();
	}
	else
	{
		return Path(pathBuffer);
	}
}

void Path::initWithString(OSString path)
{
	if (path.empty())
	{
		//TODO: log error!
		return;
	}

	StuffSim::trim(path);

	//is it a full path? attempt to determine by extracting drive
	m_drive = extractDrive(path);

	if (m_drive == 0) //not a full path
		m_fullPath = path;
	else
	{
		m_fullPath = path.substr(3, path.length() - 2);
		m_fullPath = path;
	}

	//is it a valid path?
	//if path is given with drive (fully resolved), just check if it's valid
	if (m_drive != 0 && isValid()) //we have m_fullPath set in this case.
	{
		m_valid = true;
	}
	else if (m_drive == 0) //path is relative. check if valid by adding to path of exe. 
	{
		//expensive:
		Path fullPathAttempt = getExecutablePath() + path;
		fullPathAttempt.normalize();			
		m_valid = fullPathAttempt.isValid(); 
	}
	else //path is full and invalid.
	{
		m_valid = false;
	}
}


OSString Path::appendPathStr(const OSString& otherPathStr) const
{
	bool thisHasSlash = m_fullPath.back() == OSSpecificStateImpl::m_dirDivider;
	bool otherHasSlash = otherPathStr.front() == OSSpecificStateImpl::m_dirDivider;

	if (thisHasSlash && otherHasSlash)
		return m_fullPath + otherPathStr.substr(1, otherPathStr.length() - 1);
	else if (!thisHasSlash && !otherHasSlash)
		return m_fullPath + OSSpecificStateImpl::m_dirDivider + otherPathStr;
	else
		return m_fullPath + otherPathStr;
}



OSChar Path::extractDrive(const OSString& path)
{
	//if a drive is specified, it's a full path
	size_t indexOfVolPathDivider = path.find(OSSpecificStateImpl::m_volumePathDivider);

	if (indexOfVolPathDivider != OSString::npos)
		return path[0];
	else
		return 0;
}



//statics
SSIM_MARK_GLOBAL const OSChar Path::OSSpecificStateImpl::m_dirDivider = '\\';
SSIM_MARK_GLOBAL const OSChar Path::OSSpecificStateImpl::m_rootOfCurrentDisk = '\\';
SSIM_MARK_GLOBAL const OSString Path::OSSpecificStateImpl::m_volumePathDivider = SSIM_STR_LIT(":\\");

SSIM_MARK_GLOBAL StuffSim::Path Path::s_executablePath = Path::initExecutablePath();


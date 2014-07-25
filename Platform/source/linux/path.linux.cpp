/*
	Linux implementations of platform specific functions
*/


#include "path.h"

using namespace StuffSim;


//structures and classes
struct Path::OSSpecificStateImpl
{	
	static const OSChar m_dirDivider;
	
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
void Path::normalize()
{

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
	return Path();
}


Path Path::operator+(const OSString& otherPathString) const
{
	return Path();
}


//private
Path Path::initExecutablePath()
{
	return Path();
}


OSString Path::appendPathStr(const OSString& otherPathStr) const
{
	return OSString(SSIM_STR_LIT(""));
}



OSChar Path::extractDrive(const OSString& path)
{
	return 0;
}



//statics
SSIM_MARK_GLOBAL const OSChar Path::OSSpecificStateImpl::m_dirDivider = '/';
SSIM_MARK_GLOBAL StuffSim::Path Path::s_executablePath = Path::initExecutablePath();


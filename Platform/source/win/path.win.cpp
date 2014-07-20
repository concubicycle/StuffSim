/*
	TODO: A bunch of 'new' operators.. see if you can get an allocator in here
*/

#include "path.h"
using namespace StuffSim;

#define NUM_ILLEGAL_TOKENS 1

//structures and classes
struct Path::OSSpecificStateImpl
{
	const OSString m_volumePathDivider = SS_STR_LIT(":\\");
	const OSChar m_dirDivider = '\\';
	const OSChar m_rootOfCurrentDisk = '\\';	
	static const OSString m_illegalPathStringTokens[NUM_ILLEGAL_TOKENS]; //initialized all the way at the bottom (along with other statics)

	OSSpecificStateImpl() {} //default
	OSSpecificStateImpl(const OSSpecificStateImpl& other) { }
};

Path::StaticPathState::StaticPathState()
{
	//set the executable path
	OSChar pathBuffer[_MAX_PATH];
	int pathLen = GetModuleFileNameW(NULL, pathBuffer, _MAX_PATH);
	s_executablePath = Path(pathBuffer);
	
	if (pathLen == 0)
	{
		//TODO: log error
	}
}

StuffSim::Path::StaticPathState::~StaticPathState()
{

}



//constructors
Path::Path() : m_osSpecificState(new OSSpecificStateImpl), m_valid(false) { } //default

Path::Path(OSString path) : m_osSpecificState(new OSSpecificStateImpl)
{
	initWithString(path);
}

Path::Path(const Path& path) //copy
	: m_osSpecificState(new OSSpecificStateImpl(*(path.m_osSpecificState)))
	, m_valid(path.m_valid)
	, m_drive(path.m_drive)
	, m_fullPath(path.m_fullPath)
	, m_pathString(path.m_pathString) { }


//destructors
Path::~Path() 
{

}


//public functions
//finds directory of file, or returns copy of self. 
Path Path::pathDir() const
{
	size_t indexOfLastSlash = m_fullPath.find_last_of(m_osSpecificState->m_dirDivider);
	if (indexOfLastSlash == OSString::npos)
	{
		return Path(m_fullPath);
	}
	if (indexOfLastSlash == m_fullPath.length() - 1)
	{
		return *this;
	}

	return Path(m_fullPath.substr(0, indexOfLastSlash+1));
}

Path Path::getExecutablePath()
{	
	return Path(m_staticState.s_executablePath);
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
		m_pathString = other.m_pathString;		
	}
	return *this;
}

Path Path::operator+(const Path& otherPath) const
{
	return Path(m_fullPath + otherPath.m_pathString);
}


Path Path::operator+(const OSString& otherPathString) const
{
	return Path(m_fullPath + otherPathString);
}



//////////////////////////////////////////////////////////////////////////
// UNIMPLEMENTED
void Path::normalize()
{
	//tokenize m_statePath. find special tokens, and modify the path accordingly.

}

bool Path::isValid() const
{
	return true;
}

std::uint32_t Path::getSize() const
{
	return 0;
}

bool Path::isFile() const
{
	return true;
}

bool Path::isDir() const
{
	return true;
}
//////////////////////////////////////////////////////////////////////////


//private
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
		m_pathString = path;
	else
	{
		m_pathString = path.substr(3, path.length() - 2);
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
		m_fullPath = fullPathAttempt.m_fullPath;				
		m_valid = fullPathAttempt.isValid(); 
	}
	else //path is full and invalid.
	{
		m_valid = false;
	}
}

OSChar Path::extractDrive(const OSString& path)
{
	//if a drive is specified, it's a full path
	size_t indexOfVolPathDivider = path.find(m_osSpecificState->m_volumePathDivider);
	if (indexOfVolPathDivider != OSString::npos)
		return path[0];
	else
		return 0;
}



//statics
SS_MARK_GLOBAL Path::StaticPathState Path::m_staticState;
const OSString Path::OSSpecificStateImpl::m_illegalPathStringTokens[] = { SS_STR_LIT(":") };
StuffSim::Path StuffSim::Path::StaticPathState::s_executablePath;


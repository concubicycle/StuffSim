/*
	Platform independent function that belong to Path class
*/

#include "path.h"

using namespace StuffSim;

void Path::makeFullyResolved()
{
	if (m_drive != 0)
		return;

	m_pathStr = getExecutablePath().appendPathStr(m_pathStr);
	initWithString(m_pathStr);
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
		m_pathStr = path;
	else
	{
		m_pathStr = path.substr(3, path.length() - 2);
		m_pathStr = path;
	}

	//is it a valid path?
	//if path is given with drive (fully resolved), just check if it's valid
	if (m_drive != 0 && isValid()) //we have m_pathStr set in this case.
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

Path Path::getExecutablePath()
{
	return s_executablePath;
}

bool Path::isFull() const
{
	return m_full;
}


const OSString& Path::getFullPathStr() const
{
	return m_pathStr;
}
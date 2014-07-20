#ifndef SS_PATH_H
#define SS_PATH_H

#include <cstdint>
#include <memory>
#include <utility>

#include "ss_string_util.h"


namespace StuffSim
{
	/*
		A minimal, cross-platform Path class that represents a file or directory path.
		*/
	class Path
	{
	public:
		Path();
		Path(OSString path);
		Path(const Path& path);
		~Path();

		/* turns things like C:\A\B\..\C\.\ into C:\A\C */
		void normalize();

		/* Returns the base of the path (that is, path of folder that contains the path target) */
		Path pathDir() const;

		/* Does path exist? */
		bool isValid() const;

		/* Size of this file or folder. If the path is invalid, return -1. */
		std::uint32_t getSize() const;

		/* Is this a file? */
		bool isFile() const;

		/* Is this a directory? */
		bool isDir() const;

		/* Get the path of the executable */
		//TODO: Create a policy for allowing modification of returned value.. is this possible?
		static Path getExecutablePath();

		const OSString& getFullPathStr() const;

		//operators
		Path& operator=(const Path& other);

		Path operator+ (const Path& otherPath) const;
		Path operator+ (const OSString& otherPathString) const;

	private:
		struct OSSpecificStateImpl; //os specific state

		// c++ static constructor workaround. There's a static StaticPathState member 
		// that is instantiated once before this class is used. 
		struct StaticPathState
		{
			static Path s_executablePath;

			StaticPathState();
			~StaticPathState();
		};
		
		static StaticPathState m_staticState;		
		std::unique_ptr<OSSpecificStateImpl> m_osSpecificState;

		OSString m_pathString;
		OSString m_fullPath;
		OSChar m_drive; //drive/volume on which this path resides. Empty if relative path.
		bool m_valid;		

		/* Initialize path with a path string */
		void initWithString(OSString path);

		/* If given a full path, extracts it */
		OSChar extractDrive(const OSString& path);
	};
}


#endif
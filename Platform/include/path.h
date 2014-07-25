#ifndef SSIM_PATH_H
#define SSIM_PATH_H

#include <cstdint>
#include <memory>
#include <utility>


#include "ss_string_util.h"


/* TODO:
	Create a policy for allowing modification of returned value.. is this possible?
	Create policy for whether or not to initialize self with fully resolved normalized path upon construction?
*/

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

		/* Get the path of the executable */
		static Path getExecutablePath();

		/* Turns things like C:\A\B\..\C\.\ into C:\A\C */
		void normalize();

		/* Tries to make this path fully resolved by prepending the exe path if we don't have volume */
		void makeFullyResolved();

		/* Returns the base of the path (that is, path of folder that contains the path target) */
		Path pathDir() const;
		OSString inline pathDirStr() const;

		/* Does path exist? */
		bool isValid() const;

		/* Is it a fully resolved path? */
		bool isFull() const;

		const OSString& getFullPathStr() const;

		//operators
		Path& operator=(const Path& other);

		Path operator+ (const Path& otherPath) const;
		Path operator+ (const OSString& otherPathString) const;

	private:
		struct OSSpecificStateImpl; //os specific state

		static Path s_executablePath;	
		std::unique_ptr<OSSpecificStateImpl> m_osSpecificState;

		OSString m_pathStr; //path that doesn't include volume. 
		OSChar m_drive; //drive/volume on which this path resides. Empty if relative path.
		bool m_valid;
		bool m_full;



		/* Get a path pointing to exe int s_executablePath */
		static Path initExecutablePath();

		/* Initialize path with a path string */
		void initWithString(OSString path);

		/* If given a full path, extracts it */
		OSChar extractDrive(const OSString& path);

		OSString appendPathStr(const OSString& otherPathStr) const;
	};
}


#endif
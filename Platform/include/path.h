#ifndef SS_PATH_H
#define SS_PATH_H

#include <cstdint>
#include <memory>

#include "ss_string_util.h"


namespace StuffSim
{	
	/*
		A minimal, cross-platform Path class that represents a file or directory path.	
	*/
	class Path
	{
		public:			
			Path(OSString path);
			Path(const Path& path);
			~Path();
						
			/* Returns the base of the path (that is, path of folder that contains the path target) */
			Path pathDir();

			/* Does path exist? */
			bool isValid();

			/* Size of this file or folder. If the path is invalid, return -1. */
			std::uint32_t getSize();

			/* Is this a file? */
			bool isFile();

			/* Is this a directory? */
			bool isDir();
					
			/* Get the path of the executable */
			static const OSString getExecutablePath();
						

		private:
			struct OSSpecificStateImpl;
			std::unique_ptr<OSSpecificStateImpl> m_osSpecificState;

			OSString m_drive; //drive/volume on which this path resides. Empty if relative path.
			OSString m_pathString; 
			OSString m_fullPath;
			static OSString m_executablePath; //current path of executable


			void initWithString(OSString path);
			
	};
}


#endif
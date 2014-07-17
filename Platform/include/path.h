#include <string>
#include <trim.h>
#include <cstdint>
#include <memory>

namespace StuffSumPlatform
{
	class Path
	{
		public:			
			Path(std::string path);
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

		private:
			struct OSSpecificStateImpl;
			std::unique_ptr<OSSpecificStateImpl> m_osSpecificState;

			std::string m_drive; //drive/volume on which this path resides. Empty if relative path.
			std::string m_pathString; 
			std::string m_fullPath;


	};
}
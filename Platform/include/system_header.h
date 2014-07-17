//main os stuff
#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <unistd.h>
#endif


//dll loading
#ifdef _WIN32
#define SL_EXPORT
#endif

#ifdef __linux__
#define SL_EXPORT __declspec( dllexport )
#endif
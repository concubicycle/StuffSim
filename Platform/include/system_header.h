//all the mess goes here
// you may feel like this if you go here: https://www.youtube.com/watch?v=a6YKD5hCShI&t=3m40s


#ifndef SS_SYSTEM_HEADER
#define SS_SYSTEM_HEADER

#include <string>
#include "ss_system_typenames.h"

//these have to be defined by all implementations because at least one os 
//requires them. default empty defines.
#define SS_SL_EXPORT
#define SS_MARK_GLOBAL

#if defined(_WIN32 ) || defined(_WIN64) || defined(__WIN32__) || defined (__TOS_WIN__) || defined (__WINDOWS__)
/*~~ WINDOWS ~~*/


// Includes
//
#include <windows.h>

// Defines
//
// Exportable objects (dlls) are indicated by the including this keyword. 
// These are already defined as empty for non-windows OS's, so undefine them
// before redefining to avoid compiler warnings.
#ifdef SS_SL_EXPORT 
#undef SS_SL_EXPORT
#endif
#define SS_SL_EXPORT __declspec( dllexport )

#ifdef SS_MARK_GLOBAL 
#undef SS_MARK_GLOBAL
#endif
#define SS_MARK_GLOBAL __declspec(selectany)

// Macros
//
// Use this around os string
#define SS_STR_LIT(str) L##str


// Typedefs
//
// windows uses wstring, which is implemented as a 2 byte string (as of July 2014). 
typedef std::wstring SS_OS_STRING_TYPENAME;
typedef OSString::iterator SS_STRING_ITERATOR_TYPENAME;
typedef wchar_t SS_OS_CHAR_TYPENAME;


#endif //end windows



#ifdef __linux__
/*~~ LINUX ~~*/


// Includes
#include <unistd.h>


// Defines
//



// Macros
//
// Just in case we try to use it. We shouldn't be using OSString much in linux anyway, because normal string suffices. 
#define SS_STR_LIT(str) str

// Typedefs
//
// Linux uses UTF-8 encoding for chars, and likes normal chars. There's not many reasons to use this.
typedef std::string SS_OS_STRING_TYPENAME;
typedef std::string::iterator SS_STRING_ITERATOR_TYPENAME;
typedef char SS_OS_CHAR_TYPENAME;

#endif //end linux


#endif //end system header




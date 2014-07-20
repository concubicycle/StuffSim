#include "ss_os.h"

using namespace StuffSim;

EXTERN_C IMAGE_DOS_HEADER __ImageBase; //hmmm

struct StuffSimOS::OSStateImpl
{
	//note: this won't work on pocket pc's. so if you planned to run this on pocket pc's... condolences
	const HINSTANCE m_appInstance = (HINSTANCE)&__ImageBase; //get the application instance handle

	//console stuff
	static const WORD maxConsoleLines = 500;
	int hConHandle;
	HANDLE lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	
};


StuffSimOS::StuffSimOS() : m_osState(new OSStateImpl), m_isConsoleOpen(false)
{

}

StuffSimOS::StuffSimOS(const StuffSimOS& orig)
{

}

StuffSimOS::~StuffSimOS()
{
	if (m_isConsoleOpen)
		closeConsole();
}

void StuffSimOS::openConsole()
{
	// allocate a console for this app
	if (!AllocConsole())
	{
		//TODO: log error
	}
	else
		m_isConsoleOpen = true;
}

void StuffSimOS::closeConsole()
{
	if (!FreeConsole())
	{
		//TODO: log error
	}
	else
		m_isConsoleOpen = false;
}

void StuffSimOS::redirectIOToConsole()
{	
	openConsole();
	FILE *fp;

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &(m_osState->coninfo));
	m_osState->coninfo.dwSize.Y = m_osState->maxConsoleLines;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), m_osState->coninfo.dwSize);

	// redirect unbuffered STDOUT to the console
	m_osState->lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	m_osState->hConHandle = _open_osfhandle((long)(m_osState->lStdHandle), _O_TEXT);

	if (m_osState->lStdHandle == INVALID_HANDLE_VALUE)
	{
		//TODO: Log error
		std::string err = this->getLastError();
	}

	if (m_osState->hConHandle == -1)
	{
		//TODO: log error
	}

	fp = _fdopen(m_osState->hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);

	// redirect unbuffered STDIN to the console
	m_osState->lStdHandle = GetStdHandle(STD_INPUT_HANDLE);
	m_osState->hConHandle = _open_osfhandle((long)m_osState->lStdHandle, _O_TEXT);
	fp = _fdopen(m_osState->hConHandle, "r");
	*stdin = *fp;
	setvbuf(stdin, NULL, _IONBF, 0);

	// redirect unbuffered STDERR to the console
	m_osState->lStdHandle = GetStdHandle(STD_ERROR_HANDLE);
	m_osState->hConHandle = _open_osfhandle((long)m_osState->lStdHandle, _O_TEXT);
	fp = _fdopen(m_osState->hConHandle, "w");
	*stderr = *fp;
	setvbuf(stderr, NULL, _IONBF, 0);

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well
	std::ios::sync_with_stdio();
}

void StuffSimOS::setStdIOTarget(StdIOTarget newTarget)
{
	std::lock_guard<std::mutex> guard(m_osStateMutex);

	switch (newTarget)
	{
	case StuffSim::StuffSimOS::Console:
		redirectIOToConsole();
		break;
	default:
		break;
	}
}

std::string StuffSim::StuffSimOS::getLastError()
{
	DWORD errCode = GetLastError();

	LPVOID lpMsgBuf;
	DWORD bufLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	if (bufLen)
	{
		LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
		OSString result(lpMsgStr, lpMsgStr + bufLen);
		LocalFree(lpMsgBuf);
		return  StuffSim::OSStringToCharString(result);
	}
	else
	{
		//TODO: Use logger here
		return std::string("Failed to obtain status.");
	}
}

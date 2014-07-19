/*
	Notes:

	In order for a thread to be created and not join as soon as it finishes, detach the thread. This turns it into a daemon thread.
	You are then responsible for terminating them.


*/

#include <thread>

namespace StuffSim
{
	class ThreadPool
	{
	public:
		ThreadPool();
		~ThreadPool();
	private:

	};
}
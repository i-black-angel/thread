#include <iostream>
#include <cstring>
#include "thread.h"

#ifdef _WIN32
unsigned int CALLBACK on_thread_callback(void *pvoid)
#else
void * on_thread_callback(void *pvoid)
#endif /* _WIN32 */
{
	Thread *t = static_cast<Thread *>(pvoid);
	if (NULL != t) {
		t->run();
	}
	return NULL;
}

Thread::Thread() 
{
	_self = 0;
	_routine = NULL;
}

Thread::~Thread()
{
    _routine = NULL;
}

int Thread::start()
{
	_routine = on_thread_callback;
#if defined(_WIN32) || defined(_WIN64)
	unsigned int thread_id = 0;
	HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, _routine, static_cast<void *>(this), 0, &thread_id);
	if (NULL == handle) {
		std::cerr << "can't create thread" << std::endl;
	}
#else
	int res = pthread_create(&_self, NULL, _routine, static_cast<void *>(this));
	if (0 != res) {
		std::cerr << "can't create thread: " << strerror(res) << std::endl;
	}
#endif /* _WIN32 */
	return 0;
}

void Thread::exit()
{
	pthread_exit(NULL);
}

int Thread::join()
{
	return pthread_join(_self, NULL);
}

int Thread::cancel() {
	return pthread_cancel(_self);
}

void Thread::run()
{
	// implementation in sub-class
}

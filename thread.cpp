#include <iostream>
#include <cstring>
#include <cstdio>
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

void * on_runnable_callback(void *pvoid) {
	IRunnable *r = static_cast<IRunnable *>(pvoid);
	if (NULL != r) {
		r->run();
	}
	return NULL;
}

Thread::Thread(Attr *attr) 
{
	_self = 0;
	_routine = NULL;
	_runnable = NULL;
	_attr = attr;
}

Thread::Thread(IRunnable *runnable, Attr *attr) {
	_runnable = runnable;
	_attr = attr;
}

Thread::~Thread()
{
    _routine = NULL;
	_runnable = NULL;
	_attr = NULL;
}

int Thread::start()
{
	int res = 0;
	if (NULL != _runnable) {
		_routine = on_runnable_callback;
		const pthread_attr_t *thread_attr = NULL;
		if (NULL != _attr)
			thread_attr = _attr->attr();
		res = pthread_create(&_self, thread_attr, _routine, static_cast<void *>(_runnable));
		if (0 != res) {
			std::cerr << "can't create thread: " << strerror(res) << std::endl;
		}
		return res;
	}
// #if defined(_WIN32) || defined(_WIN64)
// 	unsigned int thread_id = 0;
// 	HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, _routine, static_cast<void *>(this), 0, &thread_id);
// 	if (NULL == handle) {
// 		std::cerr << "can't create thread" << std::endl;
// 	}
// #else
	_routine = on_thread_callback;
	const pthread_attr_t *thread_attr = NULL;
	if (NULL != _attr)
		thread_attr = _attr->attr();
	res = pthread_create(&_self, thread_attr, _routine, static_cast<void *>(this));
	if (0 != res) {
		std::cerr << "can't create thread: " << strerror(res) << std::endl;
	}
// #endif /* _WIN32 */
	return res;
}

void Thread::exit()
{
	pthread_exit(NULL);
}

int Thread::join()
{
	return pthread_join(_self, NULL);
}

int Thread::detach() {
	return pthread_detach(_self);
}

int Thread::cancel() {
	return pthread_cancel(_self);
}

void Thread::run()
{
	// implementation in sub-class
}

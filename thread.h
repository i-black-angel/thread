#ifndef _THREAD_H_
#define _THREAD_H_

#ifdef _WIN32
#include <windows.h>
typedef unsigned int (__stdcall *thread_callback)(void *);
#else
#include <pthread.h>
typedef void * (*thread_callback)(void *pvoid);
#endif /* _WIN32 */

#include "attr.h"				// thread attributation

/**
 * IRunnable interface
 * 
 */
class IRunnable
{
public:
    virtual ~IRunnable() { }
	virtual void run() = 0;
};

/** 
 * Thread class
 * 
 */
class Thread
{
public:
    Thread(Attr *attr = NULL);
	Thread(IRunnable *runnable, Attr *attr = NULL);
    virtual ~Thread();
	pthread_t self() const {
		return this->_self;
	}
	// attributes
	
	// activity
	int start();
	static void exit();
	int join();
	int detach();
	int cancel();

	virtual void run();
protected:
	void set_self(pthread_t self) {
		_self = self;
	}
private:
	pthread_t _self;
	thread_callback _routine;
	IRunnable *_runnable;
	Attr *_attr;
};

#endif /* _THREAD_H_ */

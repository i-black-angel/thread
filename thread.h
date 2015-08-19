#ifndef _THREAD_H_
#define _THREAD_H_

#ifdef _WIN32
#include <windows.h>
typedef unsigned int (__stdcall *thread_callback)(void *);
#else
#include <pthread.h>
typedef void * (*thread_callback)(void *pvoid);
#endif /* _WIN32 */

/** 
 * Thread class
 * 
 */
class Thread
{
public:
    Thread();
    virtual ~Thread();
	pthread_t self() const {
		return this->_self;
	}

	int start();
	void exit();
	int join();
	int cancel();

	virtual void run();
protected:
	void set_self(pthread_t self) {
		_self = self;
	}
private:
	pthread_t _self;
	thread_callback _routine;
};

#endif /* _THREAD_H_ */

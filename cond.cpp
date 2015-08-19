#include <sys/time.h>
#include "cond.h"

Cond::Cond()
{
	// -std=c++11 or -std=gnu++11
	// _cond = PTHREAD_COND_INITIALIZER;
	pthread_cond_init(&_cond, NULL);
}

Cond::~Cond()
{
}

int Cond::wait(Mutex &mutex)
{
	return pthread_cond_wait(&_cond, mutex.mutex());
}

int Cond::timedwait(Mutex &mutex, time_t sec)
{
	struct timespec tsp;
	struct timeval now;
	gettimeofday(&now, NULL);
	tsp.tv_sec = now.tv_sec;
	tsp.tv_nsec = now.tv_usec * 1000;  /* usec to nsec */
	// add the offset to get timeout value
	tsp.tv_sec += sec;
	return pthread_cond_timedwait(&_cond, mutex.mutex(), &tsp);
}

int Cond::signal() {
	return pthread_cond_signal(&_cond);
}

int Cond::broadcast() {
	return pthread_cond_broadcast(&_cond);
}

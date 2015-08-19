#include "mutex.h"

Mutex::Mutex() 
{
	// need to be enabled by -std=c++11
	// _mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&_mutex, NULL);
}

Mutex::~Mutex()
{
    // pthread_mutex_destroy(_mutex);
}

int Mutex::lock()
{
	return pthread_mutex_lock(&_mutex);
}

int Mutex::trylock()
{
	return pthread_mutex_trylock(&_mutex);
}

int Mutex::unlock() {
	return pthread_mutex_unlock(&_mutex);
}

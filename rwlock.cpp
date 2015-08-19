#include "rwlock.h"

RWLock::RWLock() 
{
	// _rwlock = PTHREAD_RWLOCK_INITIALIZER;
	pthread_rwlock_init(&_rwlock, NULL);
}

RWLock::~RWLock()
{
    // pthread_rwlock_destroy(_rwlock);
}

int RWLock::rdlock()
{
	return pthread_rwlock_rdlock(&_rwlock);
}

int RWLock::wrlock()
{
	return pthread_rwlock_wrlock(&_rwlock);
}

int RWLock::unlock()
{
	return pthread_rwlock_unlock(&_rwlock);
}

int RWLock::tryrdlock()
{
	return pthread_rwlock_tryrdlock(&_rwlock);
}

int RWLock::trywrlock()
{
	return pthread_rwlock_trywrlock(&_rwlock);
}

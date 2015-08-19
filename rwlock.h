#ifndef _RWLOCK_H_
#define _RWLOCK_H_

#include <pthread.h>

class RWLock
{
public:
    RWLock();
    virtual ~RWLock();

	int rdlock();
	int wrlock();
	int unlock();
	int tryrdlock();
	int trywrlock();
private:
	pthread_rwlock_t _rwlock;
};

#endif /* _RWLOCK_H_ */

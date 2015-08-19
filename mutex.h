#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>

class Mutex
{
public:
    Mutex();
    virtual ~Mutex();

    int lock();
	int trylock();
	int unlock();
	pthread_mutex_t *mutex() { return &_mutex; }
private:
	pthread_mutex_t _mutex;
};

#endif /* _MUTEX_H_ */

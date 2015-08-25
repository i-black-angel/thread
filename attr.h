#ifndef _ATTR_H_
#define _ATTR_H_

#include <pthread.h>

class Attr
{
public:
	enum DetachState {
		JOINABLE,
		DETACHED
	};
public:
    Attr();
    virtual ~Attr();
	int getdetachstate() const;
	int setdetachstate(int detachstate);
	int getstack(void **stackaddr, size_t *stacksize) const; // unsupported
	int setstack(void *stackaddr, size_t stacksize);   // unsupported
	int getstacksize(size_t *stacksize) const;
	int setstacksize(size_t stacksize);
	int getguardsize(size_t *guardsize) const;
	int setguardsize(size_t guardsize);
	pthread_attr_t *attr() { return &_attr; }
private:
	pthread_attr_t _attr;
};

#endif /* _ATTR_H_ */

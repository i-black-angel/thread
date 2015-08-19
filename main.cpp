#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <locale>
#ifdef __GNUC__
#include <unistd.h>
#endif /* __GNUC__ */
#include "thread.h"
#include "mutex.h"
#include "cond.h"

using namespace std;

class MyThread : public Thread
{
public:
    MyThread() { }
    virtual ~MyThread() { }
    virtual void run() {
		pid_t pid = getpid();
        pthread_t tid = self();
		printf("subthread pid %lu tid %lu (0x%lX)\n",
			   static_cast<unsigned long>(pid),
			   static_cast<unsigned long>(tid),
			   static_cast<unsigned long>(tid));
		// std::cout << tid << std::endl;
    }
};

class WaitThread : public Thread
{
public:
    WaitThread() { }
    virtual ~WaitThread() { }
    virtual void run() {
        
    }
};

struct msg
{
    struct msg *next;
};

class Test
{
public:
    Test() { }
    virtual ~Test() { if (NULL != _work) { delete _work; _work = NULL; } }

	void test() {
		struct msg *mp;

		for (; ; ) {
			_mutex.lock();
			while (NULL == _work) {
				_cond.wait(_mutex);
			}
			_mutex.unlock();
		}
	}

	struct msg *_work;
	Mutex _mutex;
	Cond _cond;
};

int main(int argc, char *argv[])
{
	MyThread a;
	a.start();
	
	// DWORD id = GetCurrentProcessId();
	
	pid_t pid = getpid();
	pthread_t tid = pthread_self();
	printf("pid %lu tid %lu (0x%lX)\n",
		   static_cast<unsigned long>(pid),
		   static_cast<unsigned long>(tid),
		   static_cast<unsigned long>(tid));

	// struct msg *workq = new struct msg;
	Test test;
	test.test();
	pthread_exit(NULL);
}

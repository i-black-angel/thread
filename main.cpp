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
    MyThread() { printf("mythread\n"); }
    virtual ~MyThread() { printf("~mythread\n"); }
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

class DoSomething : public IRunnable
{
public:
    DoSomething() { printf("dosomething\n");}
    virtual ~DoSomething() { printf("~dosomething\n"); }
    virtual void run() {
		for (int i = 0; i < 10; ++i) {
			printf("%d\n", i);
			usleep(50000);
		}
    }
};


void test() {
	// must be very careful on object's lifetime
	MyThread a;
	a.start();
}

int main(int argc, char *argv[])
{
	// MyThread a;
	// a.start();
	
	// DWORD id = GetCurrentProcessId();
	
	// pid_t pid = getpid();
	// pthread_t tid = pthread_self();
	// printf("pid %lu tid %lu (0x%lX)\n",
	// 	   static_cast<unsigned long>(pid),
	// 	   static_cast<unsigned long>(tid),
	// 	   static_cast<unsigned long>(tid));

	// // struct msg *workq = new struct msg;
	// // Test test;
	// // test.test();
	test();
	DoSomething ds;
	Thread thread(ds);
	thread.start();

	pthread_exit(NULL);
}

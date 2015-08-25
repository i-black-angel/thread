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
#include "attr.h"
#include "thread.h"
#include "mutex.h"
#include "cond.h"

using namespace std;


class MyThread : public Thread
{
public:
    MyThread(Attr *attr = NULL) : Thread(attr) { printf("mythread\n"); }
    virtual ~MyThread() { printf("~mythread\n"); }
    virtual void run() {
		pid_t pid = getpid();
        pthread_t tid = self();
		printf("subthread pid %lu tid %lu (0x%lX)\n",
			   static_cast<unsigned long>(pid),
			   static_cast<unsigned long>(tid),
			   static_cast<unsigned long>(tid));
		// std::cout << tid << std::endl;

		Attr attr;
		printf("detachstate:%d\n", attr.getdetachstate());
		// void *stackaddr = NULL;
		size_t stacksize = 0;
		attr.getstacksize(&stacksize);
		printf("stack size: %lu\n", stacksize);
		
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


int main(int argc, char *argv[])
{
	Attr attr;
	size_t stacksize = 10 * 1024 * 1024;
	attr.setstacksize(stacksize);
	perror("setstacksize");
	
	MyThread a(&attr);
	a.start();

	size_t getsize = 0;
	attr.getstacksize(&getsize);
	printf("stacksize: %lu\n", getsize);
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
//	test();
	DoSomething ds;
	Thread thread(&ds);
	thread.start();

	// Attr attr;
	// printf("detachstate:%d\n", attr.getdetachstate());
	// void *stackaddr = NULL;
	// size_t stacksize = 0;
	// attr.getstacksize(&stacksize);
	// printf("stack size: %luM\n", stacksize / 1024 / 1024);

	printf("main exit\n");
	// Thread::exit();
	// pthread_exit(NULL);
	getchar();
	return 0;
}

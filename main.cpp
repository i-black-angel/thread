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

int main(int argc, char *argv[])
{
	MyThread a;
	a.start();

	pid_t pid = getpid();
	pthread_t tid = pthread_self();
	printf("pid %lu tid %lu (0x%lX)\n",
		   static_cast<unsigned long>(pid),
		   static_cast<unsigned long>(tid),
		   static_cast<unsigned long>(tid));
	pthread_exit(NULL);
    // return 0;
}

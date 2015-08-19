TARGET = main
CXXFLAGS = -Wall -g

$(TARGET): main.o thread.o mutex.o cond.o rwlock.o
	$(CXX) -o $@ $^ -lpthread

clean:
	-rm -f *.o $(TARGET)

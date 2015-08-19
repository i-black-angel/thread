TARGET = main

$(TARGET): main.o thread.o
	$(CXX) -o $@ main.o thread.o -lpthread

clean:
	-rm -f *.o $(TARGET)

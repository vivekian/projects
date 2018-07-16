CPPFLAGS=--std=c++14 -O2
LDFLAGS=-O2

SRCS=thread_pool.cpp main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

threadpool: $(OBJS)
	    $(CXX) $(LDFLAGS) -o threadpool thread_pool.o main.o $(LDLIBS) 

thread_pool.o: thread_pool.cpp thread_pool.h
	    $(CXX) $(CPPFLAGS) -c thread_pool.cpp

main.o: main.cpp
	    $(CXX) $(CPPFLAGS) -c main.cpp

clean: 
		rm -f threadpool $(OBJS)

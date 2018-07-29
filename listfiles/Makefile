CPPFLAGS=--std=c++14 -O2
LDFLAGS=-O2

SRCS=filesystem_tree.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

listfiles: $(OBJS)
	    $(CXX) $(LDFLAGS) -o listfiles filesystem_tree.o $(LDLIBS) 

filesystem_tree.o: filesystem_tree.cpp 
	    $(CXX) $(CPPFLAGS) -c filesystem_tree.cpp

clean: 
		rm -f listfiles $(OBJS)

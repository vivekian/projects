CPPFLAGS=--std=c++11

SRCS=trie_impl.cpp main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

wordcomplete: $(OBJS)
	    $(CXX) $(LDFLAGS) -o wordcomplete trie_impl.o main.o $(LDLIBS) 

trie_impl.o: trie_impl.cpp trie_impl.h
	    $(CXX) $(CPPFLAGS) -c trie_impl.cpp

main.o: main.cpp
	    $(CXX) $(CPPFLAGS) -c main.cpp

clean: 
		rm -f wordcomplete $(OBJS)

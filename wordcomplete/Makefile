CC = clang++
CPPFLAGS=--std=c++14
#LDFLAGS=
#LDLIBS=

SRCS=trie_impl.cpp main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

wordcomplete: $(OBJS)
	    $(CC) $(LDFLAGS) -o wordcomplete trie_impl.o main.o $(LDLIBS) 

trie_impl.o: trie_impl.cpp trie_impl.h
	    $(CC) $(CPPFLAGS) -c trie_impl.cpp

main.o: main.cpp
	    $(CC) $(CPPFLAGS) -c main.cpp

clean: 
		rm -f wordcomplete $(OBJS)

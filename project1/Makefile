spell: spellcheck.o hash.o
	g++ spellcheck.o hash.o -o spell

spellcheck.o: spellcheck.cpp hash.h
	g++ -c spellcheck.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o spell spellcheck.cpp hash.cpp
clean:
	rm -f *.o *.out

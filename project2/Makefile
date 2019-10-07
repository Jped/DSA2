useHeap.exe: useHeap.o hash.o heap.o
	clang++ -o useHeap.exe useHeap.o heap.o hash.o

useHeap.o: useHeap.cpp
	clang++ -c useHeap.cpp

heap.o: heap.cpp heap.h
	clang++ -c heap.cpp

hash.o: hash.cpp hash.h
	clang++ -c hash.cpp

debugmem:
	clang++ -Wall -Wextra -fsanitize=memory -g -o useHeapDebug.exe useHeap.cpp heap.cpp hash.cpp

debugaddr:
	clang++ -Wall -Wextra -fsanitize=address -g -o useHeapDebug.exe useHeap.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups

useHeap.exe: useHeap.o hash.o heap.o
	g++ -o useHeap.exe useHeap.o heap.o hash.o

useHeap.o: useHeap.cpp
	g++ -c useHeap.cpp

justHeap.exe: hash.o heap.o
	g++ -o justHeap.exe heap.o hash.o


heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups

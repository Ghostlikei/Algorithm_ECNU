output: QuickSort.o TimeTest.o
	g++ QuickSort.o TimeTest.o -o output

TimeTest.o: TimeTest.cpp
	g++ -c TimeTest.cpp

QuickSort.o: QuickSort.cpp QuickSort.h
	g++ -c QuickSort.cpp

clean:
	rm *.o output

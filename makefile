correct: main.o correct.o
	g++ -Wall -g main.o correct.o -o correct

main.o: main.cpp correct.h
	g++ -Wall -c main.cpp

correct.o: correct.cpp correct.h
	g++ -Wall -c correct.cpp

clean:
	rm -rf correct *.o
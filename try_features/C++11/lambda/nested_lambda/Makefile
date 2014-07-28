
run: sum.exe
	./sum.exe

sum.exe: sum.o
	g++ -o sum.exe sum.o

sum.o: sum.cpp
	g++ -c sum.cpp -std=c++11 -O2


clean:
	rm sum.exe



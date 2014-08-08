
run: header.exe
	./header.exe

header.exe: main.o B.o
	g++ -o header.exe main.o B.o

B.o: B.cpp CA.h
	g++ -o B.o -c B.cpp

main.o: main.cpp CA.h
	g++ -o main.o -c main.cpp

clean:
	rm -f main.o B.o header.exe



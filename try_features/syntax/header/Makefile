
run: header.exe
	./header.exe

header.exe: CA.o main.o
	g++ -o header.exe CA.o main.o

CA.o: CA.cpp CA.h
	g++ -o CA.o -c CA.cpp

main.o: main.cpp CA.h
	g++ -o main.o -c main.cpp

clean:
	rm -f CA.o main.o header.exe




test1: test1.exe
	./test1.exe

test2: test2.exe
	./test2.exe

test1.exe: unique_ptr.cpp
	g++ -o test1.exe -O2 -std=c++11 -DTEST1 unique_ptr.cpp

test2.exe: unique_ptr.cpp
	g++ -o test2.exe -O2 -std=c++11 -DTEST2 unique_ptr.cpp

clean:
	rm -f test1.exe test2.exe



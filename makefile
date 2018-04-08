all:
	g++ -std=c++11 src/myhello.cpp -o bin/myhello -I.
	g++ -std=c++11 src/mycat.cpp -o bin/mycat -I.
	g++  -std=c++11 main.cpp -o myshell -I.

clean:
	rm bin/*
	rm -f myshell

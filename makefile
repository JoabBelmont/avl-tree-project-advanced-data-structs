run: build/main.o
	g++ build/main.o -o build/run
	./build/run

build/main.o: src/main.cpp src/main-functions.hpp
	g++ -c src/main.cpp -o build/main.o

clean:
	rm -rf build/*

run: build/main.o
	g++ build/main.o -o build/run
	./build/run

build/main.o: src/main/main.cpp
	g++ -c src/main/main.cpp -o build/main.o

clean:
	rm -rf build/*

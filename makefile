run: build/main.o build/avl.o
	g++ build/main.o build/avl.o -o build/run
	./build/run

build/main.o: src/main.cpp src/avl.hpp
	g++ -c src/main.cpp -o build/main.o

build/avl.o: src/avl.cpp src/avl.hpp src/data-classes/person.hpp src/data-classes/nationalId.hpp src/data-classes/date.hpp src/node.hpp
	g++ -c src/avl.cpp -o build/avl.o

clean:
	rm -rf build/*

.PHONY: run clean

run: main.o avl.o
	g++ main.o avl.o -o run

main.o: main.cpp avl.hpp
	g++ -c main.cpp

avl.o: avl.cpp avl.hpp pessoa.hpp date.hpp node.hpp
	g++ -c avl.cpp

clean:
	rm *.o run
all:
	g++ -o ./build/projeto src/*.cpp -I./includes -O3 -std=c++11
run:
	./build/projeto
val:
	g++ -o projeto src/*.cpp -I./includes -g -O0 
	valgrind --leak-check=yes ./projeto
build:
	g++ ./src/*/*.cpp ./src/*/*.hpp main.cpp -lGL -lGLU -lglut  -o test.out 
run:
	mangohud ./test.out
debug:
	g++ ./src/*/*.cpp ./src/*/*.hpp main.cpp -lGL -lGLU -lglut  -o test.out -p 
	gdb ./test.out

a.out : main.cpp 
	g++ main.cpp -lSDL2 -lpthread  -std=c++11 ellipse  SDL2_rotozoom.o

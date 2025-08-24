all: sort

sort: visualizer.o visual.o
	g++ -o sort visualizer.o visual.o -lsfml-graphics -lsfml-window -lsfml-system

visual.o: visual.cpp
	g++ -c visual.cpp -lsfml-graphics -lsfml-window -lsfml-system

visualizer.o: visualizer.cpp
	g++ -c visualizer.cpp -lsfml-graphics -lsfml-window -lsfml-system

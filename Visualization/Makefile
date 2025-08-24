all: sort

sort: visualizer.o visual.o arrutil.o
	g++ -o sort visualizer.o visual.o arrutil.o -lsfml-graphics -lsfml-window -lsfml-system

visual.o: visual.cpp visualizer.h
	g++ -c visual.cpp

visualizer.o: visualizer.cpp visualizer.h arrutil.o
	g++ -c visualizer.cpp

arrayutil.o: arrutil.cpp arrutil.h
	g++ -c arrutil.cpp

clean:
	rm -f *.o sort

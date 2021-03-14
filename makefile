CC = g++
DEP = -lsfml-graphics -lsfml-window -lsfml-system ./Algo/Algo.cpp ./Grid/Grid.cpp  ./Grid_Window/Grid_Window.cpp
NAME = searchAlgo
all:
	$(CC) $(NAME).cpp $(DEP) -o $(NAME).exe
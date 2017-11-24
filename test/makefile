#define header and source folders
HEADER = ../include
SOURCE = ../src

#define all flags
CCFLAGS = -c -I $(HEADER)

#create executalbe file by linking the object files
a.out: Board.o Player.o HumanPlayer.o ComputerPlayer.o Location.o MoveLogic.o StandardMoveLogic.o ViewByConsole.o Menu.o GameManager.o main.o
	g++ Board.o Player.o HumanPlayer.o ComputerPlayer.o Location.o MoveLogic.o StandardMoveLogic.o ViewByConsole.o Menu.o GameManager.o main.o

#creating all object files from source code
Board.o: $(SOURCE)/Board.cpp $(HEADER)/Board.h $(HEADER)/Location.h
	g++ $(CCFLAGS) $(SOURCE)/Board.cpp 

Player.o: $(SOURCE)/Player.cpp $(HEADER)/Player.h $(HEADER)/Location.h
	g++ $(CCFLAGS) $(SOURCE)/Player.cpp

HumanPlayer.o: $(SOURCE)/HumanPlayer.cpp $(HEADER)/HumanPlayer.h $(HEADER)/Player.h
	g++ $(CCFLAGS) $(SOURCE)/HumanPlayer.cpp
	
ComputerPlayer.o: $(SOURCE)/ComputerPlayer.cpp $(HEADER)/ComputerPlayer.h $(HEADER)/Player.h
	g++ $(CCFLAGS) $(SOURCE)/ComputerPlayer.cpp
	
Location.o: $(SOURCE)/Location.cpp $(HEADER)/Location.h
	g++ $(CCFLAGS) $(SOURCE)/Location.cpp

MoveLogic.o: $(SOURCE)/MoveLogic.cpp $(HEADER)/MoveLogic.h $(HEADER)/Player.h $(HEADER)/Location.h
	g++ $(CCFLAGS) $(SOURCE)/MoveLogic.cpp

StandardMoveLogic.o: $(SOURCE)/StandardMoveLogic.cpp $(HEADER)/StandardMoveLogic.h $(HEADER)/MoveLogic.h
	g++ $(CCFLAGS) $(SOURCE)/StandardMoveLogic.cpp

ViewByConsole.o: $(SOURCE)/ViewByConsole.cpp $(HEADER)/ViewByConsole.h $(HEADER)/ViewGame.h
	g++ $(CCFLAGS) $(SOURCE)/ViewByConsole.cpp
	
Menu.o: $(SOURCE)/Menu.cpp $(HEADER)/Menu.h $(HEADER)/Player.h $(HEADER)/ViewGame.h
	g++ $(CCFLAGS) $(SOURCE)/Menu.cpp
	
GameManager.o: $(SOURCE)/GameManager.cpp $(HEADER)/GameManager.h $(HEADER)/Board.h $(HEADER)/MoveLogic.h $(HEADER)/Player.h
	g++ $(CCFLAGS) $(SOURCE)/GameManager.cpp
	
main.o: $(SOURCE)/main.cpp $(HEADER)/GameManager.h $(HEADER)/HumanPlayer.h $(HEADER)/StandardMoveLogic.h $(HEADER)/Board.h $(HEADER)/Player.h $(HEADER)/ViewByConsole.h $(HEADER)/Menu.h
	g++ $(CCFLAGS) $(SOURCE)/main.cpp
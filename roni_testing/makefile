INCLUDE = ../include/
SRC = ../src/
CCFLAGS = -Wall -c -I $(INCLUDE) -ggdb

#create executalbe file by linking the object files
a.out: Board.o Player.o HumanPlayer.o ComputerPlayer.o Location.o MoveLogic.o StandardMoveLogic.o ViewByConsole.o Client.o GameManager.o LocalGameManager.o RemoteGameManager.o Menu.o main.o
	g++ Board.o Player.o HumanPlayer.o ComputerPlayer.o Location.o MoveLogic.o StandardMoveLogic.o ViewByConsole.o Client.o GameManager.o LocalGameManager.o RemoteGameManager.o Menu.o main.o

#creating all object files from source code

Board.o: $(SRC)Board.cpp $(INCLUDE)Board.h $(INCLUDE)Location.h
	g++ $(CCFLAGS) $(SRC)Board.cpp

Player.o: $(SRC)Player.cpp $(INCLUDE)Player.h $(INCLUDE)Location.h
	g++ $(CCFLAGS) $(SRC)Player.cpp

HumanPlayer.o: $(SRC)HumanPlayer.cpp $(INCLUDE)HumanPlayer.h $(INCLUDE)Player.h
	g++ $(CCFLAGS) $(SRC)HumanPlayer.cpp
	
ComputerPlayer.o: $(SRC)ComputerPlayer.cpp $(INCLUDE)ComputerPlayer.h $(INCLUDE)Player.h
	g++ $(CCFLAGS) $(SRC)ComputerPlayer.cpp
	
Location.o: $(SRC)Location.cpp $(INCLUDE)Location.h
	g++ $(CCFLAGS) $(SRC)Location.cpp

MoveLogic.o: $(SRC)MoveLogic.cpp $(INCLUDE)MoveLogic.h $(INCLUDE)Player.h $(INCLUDE)Location.h
	g++ $(CCFLAGS) $(SRC)MoveLogic.cpp

StandardMoveLogic.o: $(SRC)StandardMoveLogic.cpp $(INCLUDE)StandardMoveLogic.h $(INCLUDE)MoveLogic.h
	g++ $(CCFLAGS) $(SRC)StandardMoveLogic.cpp

ViewByConsole.o: $(SRC)ViewByConsole.cpp $(INCLUDE)ViewByConsole.h $(INCLUDE)ViewGame.h
	g++ $(CCFLAGS) $(SRC)ViewByConsole.cpp

Client.o: $(SRC)Client.cpp $(INCLUDE)Client.h $(INCLUDE)Location.h
	g++ $(CCFLAGS) $(SRC)Client.cpp
	
GameManager.o: $(SRC)GameManager.cpp $(INCLUDE)GameManager.h $(INCLUDE)Board.h $(INCLUDE)MoveLogic.h $(INCLUDE)Player.h
	g++ $(CCFLAGS) $(SRC)GameManager.cpp
	
LocalGameManager.o: $(SRC)LocalGameManager.cpp $(INCLUDE)LocalGameManager.h $(INCLUDE)GameManager.h
	g++ $(CCFLAGS) $(SRC)LocalGameManager.cpp
	
RemoteGameManager.o: $(SRC)RemoteGameManager.cpp $(INCLUDE)RemoteGameManager.h $(INCLUDE)GameManager.h $(INCLUDE)Client.h
	g++ $(CCFLAGS) $(SRC)RemoteGameManager.cpp

Menu.o: $(SRC)Menu.cpp $(INCLUDE)Menu.h $(INCLUDE)Player.h $(INCLUDE)ViewGame.h $(INCLUDE)GameManager.h
	g++ $(CCFLAGS) $(SRC)Menu.cpp
	
main.o: $(SRC)main.cpp $(INCLUDE)GameManager.h $(INCLUDE)HumanPlayer.h $(INCLUDE)StandardMoveLogic.h $(INCLUDE)Board.h $(INCLUDE)Player.h $(INCLUDE)ViewByConsole.h $(INCLUDE)Menu.h
	g++ $(CCFLAGS) $(SRC)main.cpp

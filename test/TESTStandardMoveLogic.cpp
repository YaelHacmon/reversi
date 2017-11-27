
#include  "../include/StandardMoveLogic.h"
#include "../gtest_src/gtest/gtest.h"


TEST(StandardMoveLogic,playMove){
	StandardMoveLogic st;
	Board b;
	Player* blackPLayer = new HumanPlayer("X",Board::BLACK);
	Player* whitePlayer = new HumanPlayer("O",Board::WHITE);

	st.playMove(Location(3,4),blackPLayer,b,whitePlayer);
	EXPECT_EQ(Board::BLACK,b.getCell(Location(3,4)));
	EXPECT_EQ(Board::BLACK,b.getCell(Location(4,4)));

	st.playMove(Location(3,3),whitePlayer,b,blackPLayer);
	EXPECT_EQ(Board::WHITE,b.getCell(Location(3,3)));
	EXPECT_EQ(Board::WHITE,b.getCell(Location(4,4)));

	//testing edge
	b.makeInColor(Board::BLACK,Location(4,6));
	b.makeInColor(Board::WHITE,Location(3,7));

	st.playMove(Location(2,8),blackPLayer,b,whitePlayer);
	EXPECT_EQ(Board::BLACK,b.getCell(Location(2,8)));
	EXPECT_EQ(Board::BLACK,b.getCell(Location(3,7)));
}

TEST(StandardMoveLogic,updateMoveOptions){

	StandardMoveLogic st;
	Board b;
	Player* blackPlayer = new HumanPlayer("X",Board::BLACK);
	Player* whitePlayer = new HumanPlayer("O",Board::WHITE)
	st.updateMoveOptions(blackPlayer,b);

	std::vector<Location> vec = blackPlayer->getPossibleMoves();
	EXPECT_EQ(vec.size(),4);
	EXPECT_EQ(vec[o],Location(3,4));
	EXPECT_EQ(vec[1],Location(4,3));
	EXPECT_EQ(vec[2],Location(5,6));
	EXPECT_EQ(vec[3],Location(6,5));

	b.makeInColor(Board::BLACK,Location(4,4));
	b.makeInColor(Board::BLACK,Location(3,4));

	st.updateMoveOptions(whitePlayer,b);
	std::vector<Location> vec = whitePlayer->getPossibleMoves();
	EXPECT_EQ(vec[o],Location(3,3));
	EXPECT_EQ(vec[1],Location(3,5));
	EXPECT_EQ(vec[2],Location(5,3));

}

TEST(StandardMoveLogic,canPlayTurn){
	StandardMoveLogic st;
	Board b;
	Player* blackPLayer = new HumanPlayer("X",Board::BLACK);
	st.updateMoveOptions(blackPLayer,b);
	EXPECT_EQ(st.canPlayTurn(blackPLayer),true);

	//test for no move
	for (int i = 0; i < b.size(); ++i){
		for(int j = 0; j < b.size(); ++i){
			b.makeInColor(Board::BLACK,Location(i,j));
		}
	}
	st.updateMoveOptions(blackPLayer,b);
	EXPECT_EQ(st.canPlayTurn(blackPLayer),false);	
}


TEST(StandardMoveLogic,isMoveAllowedAndisPossibleMove){
	StandardMoveLogic st;
	Board b;
	Player* blackPLayer = new HumanPlayer("X",Board::BLACK);

	EXPECT_EQ(st.isPossibleMoveByLogic(Board::BLACK,Location(3,4),b),true);
	EXPECT_EQ(st.isPossibleMoveByLogic(Board::BLACK,Location(6,7),b),false);

	st.updateMoveOptions(blackPLayer,b);

	EXPECT_EQ(st.isMoveAllowed(Location(3,4),blackPLayer),true);
	EXPECT_EQ(st.isMoveAllowed(Location(6,7),blackPLayer),false);
}

TEST(StandardMoveLogic,lastInColorRange){
	StandardMoveLogic st;
	Board b;
	Player* blackPLayer = new HumanPlayer("X",Board::BLACK);
	b.makeInColor(Board::BLACK,Location(2,5));
	b.makeInColor(Board::BLACK,Location(1,6));
	b.makeInColor(Board::WHITE,Location(0,7));
	b.makeInColor(Board::BLACK,Location(3,5));
	b.makeInColor(Board::BLACK,Location(3,6));
	b.makeInColor(Board::WHITE,Location(3,7));
	b.makeInColor(Board::WHITE,Location(5,5));
	b.makeInColor(Board::BLACK,Location(6,6));
	b.makeInColor(Board::WHITE,Location(5,4));
	b.makeInColor(Board::WHITE,Location(6,4));
	b.makeInColor(Board::BLACK,Location(7,4));

	//test for all the diractions
	
	//left up
	Location rus = st.lastInColorRange(Board::BLACK,Location(3,4),Location(0,0),b);
	EXPECT_EQ(rus,Location(3,4));

	//up
	Location rus = st.lastInColorRange(Board::BLACK,Location(3,4),Location(0,4),b);
	EXPECT_EQ(rus,Location(3,4));

	//right up
	Location rus = st.lastInColorRange(Board::BLACK,Location(3,4),Location(0,7),b);
	EXPECT_EQ(rus,Location(1,6));
	
	//right
	Location rus = st.lastInColorRange(Board::BLACK,Location(3,4),Location(3,7),b);
	EXPECT_EQ(rus,Location(3,6));
	
	//right down
	Location rus = st.lastInColorRange(Board::WHITE,Location(4,4),Location(7,7),b);
	EXPECT_EQ(rus,Location(5,5));

	//down
	Location rus = st.lastInColorRange(Board::WHITE,Location(4,4),Location(7,4),b);
	EXPECT_EQ(rus,Location(6,4));
		
	//left down
	Location rus = st.lastInColorRange(Board::WHITE,Location(4,4),Location(7,0),b);
	EXPECT_EQ(rus,Location(4,4));

	//left
	Location rus = st.lastInColorRange(Board::WHITE,Location(4,4),Location(4,0),b);
	EXPECT_EQ(rus,Location(4,4));
		
}


TEST(StandardMoveLogic,jumps){

	StandardMoveLogic st;

	EXPECT_EQ(st.jumps(4,7),1);
	EXPECT_EQ(st.jumps(7,4),-1);
	EXPECT_EQ(st.jumps(7,7),0);
}

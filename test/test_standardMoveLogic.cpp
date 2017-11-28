
#include  "../include/StandardMoveLogic.h"
#include "../gtest_src/gtest/gtest.h"
#include "../include/HumanPlayer.h"

TEST(StandardMoveLogic,updateMoveOptions){

	StandardMoveLogic st;
	Board b;
	Player* blackPlayer = new HumanPlayer("X",Board::BLACK);
	Player* whitePlayer = new HumanPlayer("O",Board::WHITE);
	st.updateMoveOptions(blackPlayer,b);

	std::vector<Location> vec = blackPlayer->getPossibleMoves();
	EXPECT_EQ(vec[0],Location(2,3));
	EXPECT_EQ(vec[1],Location(3,2));
	EXPECT_EQ(vec[2],Location(4,5));
	EXPECT_EQ(vec[3],Location(5,4));

	delete blackPlayer;
	delete whitePlayer;
}


TEST(StandardMoveLogic,playMove){
	StandardMoveLogic st;
	Board b;
	Player* blackPLayer = new HumanPlayer("X",Board::BLACK);
	Player* whitePlayer = new HumanPlayer("O",Board::WHITE);

	st.updateMoveOptions(blackPLayer, b);
	st.playMove(Location(3,2),blackPLayer,b,whitePlayer);
	EXPECT_TRUE(b.isCellBlack(Location(3,2)));
	EXPECT_TRUE(b.isCellBlack(Location(3,3)));

	st.updateMoveOptions(whitePlayer, b);
	st.playMove(Location(4,2),whitePlayer,b,blackPLayer);
	EXPECT_TRUE(b.isCellWhite(Location(4,2)));
	EXPECT_TRUE(b.isCellWhite(Location(4,3)));

	//testing edge
	b.makeInColor(Board::BLACK,Location(3,5));
	b.makeInColor(Board::WHITE,Location(2,6));

	st.updateMoveOptions(blackPLayer, b);
	st.playMove(Location(1,7),blackPLayer,b,whitePlayer);
	EXPECT_TRUE(b.isCellBlack(Location(1,7)));
	EXPECT_TRUE(b.isCellBlack(Location(2,6)));

	delete blackPLayer;
	delete whitePlayer;
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
			if (b.isCellEmpty(Location(i,j))) {
				b.makeInColor(Board::BLACK,Location(i,j));
			}
		}
	}
	st.updateMoveOptions(blackPLayer,b);
	EXPECT_EQ(st.canPlayTurn(blackPLayer),false);

	delete blackPLayer;
}


TEST(StandardMoveLogic,isMoveAllowed){
	StandardMoveLogic st;
	Board b;
	Player* blackPLayer = new HumanPlayer("X",Board::BLACK);

	st.updateMoveOptions(blackPLayer,b);

	EXPECT_TRUE(st.isMoveAllowed(Location(2,3),blackPLayer));
	EXPECT_FALSE(st.isMoveAllowed(Location(5,6),blackPLayer));

	delete blackPLayer;
}

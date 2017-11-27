#include "../include/Board.h"
#include "../gtest_src/gtest/gtest.h"

TEST(Board,Board){
	Board b(5);
	EXPECT_EQ(5,b.size());
}

TEST(Board,BoardCopyConstructor){
	Board b(7);
	Board c(b);
	EXPECT_EQ(c.size(),7);
}

TEST(Board,isCellWhite){
	Board b;
	b.makeInColor(Board::WHITE, Location(1,1));
	EXPECT_TRUE(b.isCellWhite(Location(1,1)));
	EXPECT_FALSE(b.isCellWhite(Location(4,3)));
}

TEST(Board,isCellBlack){
	Board b;
	b.makeInColor(Board::WHITE,Location(1,1));
	EXPECT_FALSE(b.isCellBlack(Location(1,1)));
	EXPECT_TRUE(b.isCellBlack(Location(4,3)));
}

TEST(Board,isCellEmpty){
	Board b;
	EXPECT_TRUE(b.isCellEmpty(Location(1,1)));
	EXPECT_FALSE(b.isCellEmpty(Location(4,3)));
}

TEST(Board,compareCellColors){
	Board b;
	bool rus = b.compareCellColors(Location(3,4),Location(4,3));
	EXPECT_TRUE(rus);
	bool rus2 = b.compareCellColors(Location(3,3),Location(4,3));
	EXPECT_FALSE(rus2);
}

TEST(Board,SeccompareCellColors){

	Board b;
	bool rus = b.compareCellColors(Board::WHITE,Location(3,3));
	EXPECT_TRUE(rus);
	bool rus2 = b.compareCellColors(Board::BLACK,Location(3,3));
	EXPECT_FALSE(rus2);
}

TEST(Board,makeInColor){
	Board b;
	b.makeInColor(Board::WHITE,Location(1,1));
	EXPECT_TRUE(b.isCellWhite(Location(1,1)));
	EXPECT_FALSE(b.isCellEmpty(Location(1,1)));
}

TEST(Board,flipColorInRange){
	Board b;
	b.makeInColor(Board::WHITE, Location(1,1));
	b.makeInColor(Board::WHITE, Location(1,2));
	b.makeInColor(Board::WHITE, Location(1,3));
	b.flipColorInRange(Location(1,1), Location(1,3),1,1);
	EXPECT_TRUE(b.isCellBlack(Location(1,1)));
	EXPECT_TRUE(b.isCellBlack(Location(1,2)));
	EXPECT_TRUE(b.isCellBlack(Location(1,3)));
}

TEST(Board,isInBoardRange){
	Board b;
	EXPECT_TRUE(b.isInBoardRange(Location(1,1)));
	EXPECT_FALSE(b.isInBoardRange(Location(b.size()+1,1)));
}

TEST(Board,isEdge){
	Board b;
	EXPECT_FALSE(b.isEdge(Location(1,1)));
	EXPECT_TRUE(b.isEdge(Location(b.size(),b.size())));
	EXPECT_TRUE(b.isEdge(Location(b.size(),0)));
	EXPECT_TRUE(b.isEdge(Location(0,b.size())));
	EXPECT_TRUE(b.isEdge(Location(0,0)));
}

TEST(Board,isBoardFull){
	Board b;
	EXPECT_FALSE(b.isBoardFull());
	for (int i = 0; i < b.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			b.makeInColor(Board::WHITE,Location(i,j));
		}
	}
	EXPECT_TRUE(b.isBoardFull());
}


























/*
 * File:   VolcanoBoardTest.cpp
 * Author: squish
 *
 * Created on 15/08/2015, 4:23:56 PM
 */

#include "VolcanoBoardTest.h"
#include "../VolcanoBoard.h"


CPPUNIT_TEST_SUITE_REGISTRATION(VolcanoBoardTest);

VolcanoBoardTest::VolcanoBoardTest() {
}

VolcanoBoardTest::~VolcanoBoardTest() {
}

void VolcanoBoardTest::setUp() {
}

void VolcanoBoardTest::tearDown() {
}

void VolcanoBoardTest::testCalculateScore_SolidPyramid() {
    bool player = 0;
    VolcanoBoard volcanoBoard;
    volcanoBoard.capturePiece(Pyramid(3,1), player);
    volcanoBoard.capturePiece(Pyramid(3,2), player);
    volcanoBoard.capturePiece(Pyramid(3,3), player);
    int result = volcanoBoard.calculateScore(player);
    CPPUNIT_ASSERT(result == 7);
}

void VolcanoBoardTest::testCalculateScore_SolidPyramid_Remainders() {
    bool player = 0;
    VolcanoBoard volcanoBoard;
    volcanoBoard.capturePiece(Pyramid(3,1), player);
    volcanoBoard.capturePiece(Pyramid(3,2), player);
    volcanoBoard.capturePiece(Pyramid(3,3), player);
    volcanoBoard.capturePiece(Pyramid(3,2), player);
    volcanoBoard.capturePiece(Pyramid(2,2), player);
    int result = volcanoBoard.calculateScore(player);
    CPPUNIT_ASSERT(result == 9);
}

void VolcanoBoardTest::testCalculateScore_MixedPyramid() {
    bool player = 0;
    VolcanoBoard volcanoBoard;
    volcanoBoard.capturePiece(Pyramid(1,1), player);
    volcanoBoard.capturePiece(Pyramid(2,2), player);
    volcanoBoard.capturePiece(Pyramid(3,3), player);
    int result = volcanoBoard.calculateScore(player);
    CPPUNIT_ASSERT(result == 5);
}

void VolcanoBoardTest::testCalculateScore_MixedPyramid_Remainders() {
    bool player = 0;
    VolcanoBoard volcanoBoard;
    volcanoBoard.capturePiece(Pyramid(1,1), player);
    volcanoBoard.capturePiece(Pyramid(2,1), player);
    volcanoBoard.capturePiece(Pyramid(2,2), player);
    volcanoBoard.capturePiece(Pyramid(3,2), player);
    volcanoBoard.capturePiece(Pyramid(3,3), player);
    int result = volcanoBoard.calculateScore(player);
    CPPUNIT_ASSERT(result == 7);
}

void VolcanoBoardTest::testCalculateScore_AllOfTheAbove() {
    bool player = 0;
    VolcanoBoard volcanoBoard;
    volcanoBoard.capturePiece(Pyramid(1,1), player);
    volcanoBoard.capturePiece(Pyramid(1,1), player);
    volcanoBoard.capturePiece(Pyramid(1,2), player);
    volcanoBoard.capturePiece(Pyramid(1,3), player);
    volcanoBoard.capturePiece(Pyramid(2,2), player);
    volcanoBoard.capturePiece(Pyramid(3,3), player);
    volcanoBoard.capturePiece(Pyramid(3,3), player);
    int result = volcanoBoard.calculateScore(player);
    CPPUNIT_ASSERT(result == 13);
}

void VolcanoBoardTest::testCalculateScore_NothingConnects() {
    bool player = 0;
    VolcanoBoard volcanoBoard;
    volcanoBoard.capturePiece(Pyramid(1,1), player);
    volcanoBoard.capturePiece(Pyramid(3,3), player);
    volcanoBoard.capturePiece(Pyramid(4,1), player);
    int result = volcanoBoard.calculateScore(player);
    CPPUNIT_ASSERT(result == 3);
}

void VolcanoBoardTest::testCanCapturePiece() {
    VolcanoBoard vb;
    GridReference gr(2,2);
    vb.putPyramid(Pyramid(0,1), gr); // so I know how many pips top piece has
    CPPUNIT_ASSERT(vb.canCapturePiece(Pyramid(0,1), gr)); // identical piece
    CPPUNIT_ASSERT(!vb.canCapturePiece(Pyramid(0,2), gr)); // same colour, diff pips
    CPPUNIT_ASSERT(vb.canCapturePiece(Pyramid(1,1), gr)); // diff colour, same pips
    CPPUNIT_ASSERT(!vb.canCapturePiece(Pyramid(2,2), gr)); // all diff
}

void VolcanoBoardTest::testErupt() {
    VolcanoBoard vb;
    vb.init();
    GridReference gr = (0,0);
    Direction di(1,1);
    CPPUNIT_ASSERT(vb.willErupt(gr, di));
    CPPUNIT_ASSERT(vb.erupt(gr, di));
    
    CPPUNIT_ASSERT(vb.calculateScore() == 1);
    CPPUNIT_ASSERT(vb.getStack(gr).size() == 0);
    CPPUNIT_ASSERT(vb.getStack(GridReference(1,1)).size() == 3);
    CPPUNIT_ASSERT(vb.getStack(GridReference(2,2)).size() == 3);
    CPPUNIT_ASSERT(vb.getStack(GridReference(3,3)).size() == 4);
    CPPUNIT_ASSERT(vb.getStack(GridReference(4,4)).size() == 4);
}

void VolcanoBoardTest::testErupt_diffBlackCaps() {
    // if black cap in the way of eruption
    VolcanoBoard vb;
    vb.initPyramids();
    GridReference gr = (0,0);
    Direction di(1,1);
    CPPUNIT_ASSERT(vb.willErupt(gr, di));
    BlackCaps diffBC;
    diffBC.addCap(GridReference(2,2));
    CPPUNIT_ASSERT(!vb.willErupt(gr, di, diffBC));
}

void VolcanoBoardTest::testErupt_blackCap() {
    // if black cap in the way of eruption
    VolcanoBoard vb;
    vb.initPyramids();
    GridReference gr = (0,0);
    Direction di(1,1);
    CPPUNIT_ASSERT(vb.willErupt(gr, di));
    vb.putCap(GridReference(2,2));
    CPPUNIT_ASSERT(!vb.willErupt(gr, di));
    CPPUNIT_ASSERT(!vb.erupt(gr, di));
}

void VolcanoBoardTest::testErupt_offBoard() {
    // if erupting off board
    VolcanoBoard vb;
    vb.init();
    GridReference gr = (0,0);
    Direction di(-1,-1);
    CPPUNIT_ASSERT(!vb.willErupt(gr, di));
    CPPUNIT_ASSERT(!vb.erupt(gr, di));
    gr = (1,1);
    CPPUNIT_ASSERT(!vb.willErupt(gr, di));
    CPPUNIT_ASSERT(!vb.erupt(gr, di));
}

void VolcanoBoardTest::testErupt_emptyStack() {
    VolcanoBoard vb;
    GridReference gr = (2,2);
    Direction di(1,1);
    std::vector<Pyramid>& volc = vb.getStack(gr);
    CPPUNIT_ASSERT(volc.size() == 0);
    CPPUNIT_ASSERT(!vb.willErupt(gr, di));
    CPPUNIT_ASSERT(!vb.erupt(gr, di));
}

void VolcanoBoardTest::testIsGameOver_p1() {
    VolcanoBoard vb;
    bool player = 0;
    CPPUNIT_ASSERT(!vb.isGameOver(player));
    CPPUNIT_ASSERT(!vb.isGameOver());
    vb.capturePiece(Pyramid(0,1), player);
    CPPUNIT_ASSERT(!vb.isGameOver(player));
    CPPUNIT_ASSERT(!vb.isGameOver());
    vb.capturePiece(Pyramid(1,1), player);
    CPPUNIT_ASSERT(!vb.isGameOver(player));
    CPPUNIT_ASSERT(!vb.isGameOver());
    vb.capturePiece(Pyramid(2,1), player);
    CPPUNIT_ASSERT(!vb.isGameOver(player));
    CPPUNIT_ASSERT(!vb.isGameOver());
    vb.capturePiece(Pyramid(3,1), player);
    CPPUNIT_ASSERT(!vb.isGameOver(player));
    CPPUNIT_ASSERT(!vb.isGameOver());
    vb.capturePiece(Pyramid(4,1), player);
    CPPUNIT_ASSERT(vb.isGameOver(player));
    CPPUNIT_ASSERT(vb.isGameOver());
}

void VolcanoBoardTest::testIsGameOver_p2() {
    VolcanoBoard vb;
    bool player = 1;
    CPPUNIT_ASSERT(!vb.isGameOver(player));
    CPPUNIT_ASSERT(!vb.isGameOver());
    vb.capturePiece(Pyramid(0,1), player);
    CPPUNIT_ASSERT(!vb.isGameOver(player));
    CPPUNIT_ASSERT(!vb.isGameOver());
    vb.capturePiece(Pyramid(1,1), player);
    CPPUNIT_ASSERT(!vb.isGameOver(player));
    CPPUNIT_ASSERT(!vb.isGameOver());
    vb.capturePiece(Pyramid(2,1), player);
    CPPUNIT_ASSERT(!vb.isGameOver(player));
    CPPUNIT_ASSERT(!vb.isGameOver());
    vb.capturePiece(Pyramid(3,1), player);
    CPPUNIT_ASSERT(!vb.isGameOver(player));
    CPPUNIT_ASSERT(!vb.isGameOver());
    vb.capturePiece(Pyramid(4,1), player);
    CPPUNIT_ASSERT(vb.isGameOver(player));
    CPPUNIT_ASSERT(vb.isGameOver());
}

void VolcanoBoardTest::testHasATree_p1() {
    VolcanoBoard vb;
    bool player = 0;
    CPPUNIT_ASSERT(!vb.hasATree(player));
    CPPUNIT_ASSERT(!vb.hasATree());
    vb.capturePiece(Pyramid(0,1), player);
    CPPUNIT_ASSERT(!vb.hasATree(player));
    CPPUNIT_ASSERT(!vb.hasATree());
    vb.capturePiece(Pyramid(0,2), player);
    CPPUNIT_ASSERT(!vb.hasATree(player));
    CPPUNIT_ASSERT(!vb.hasATree());
    vb.capturePiece(Pyramid(2,3), player);
    CPPUNIT_ASSERT(vb.hasATree(player));
    CPPUNIT_ASSERT(vb.hasATree());
    // mixed-colour tree
}

void VolcanoBoardTest::testHasATree_p2() {
    VolcanoBoard vb;
    bool player = 1;
    CPPUNIT_ASSERT(!vb.hasATree(player));
    CPPUNIT_ASSERT(!vb.hasATree());
    vb.capturePiece(Pyramid(0,1), player);
    CPPUNIT_ASSERT(!vb.hasATree(player));
    CPPUNIT_ASSERT(!vb.hasATree());
    vb.capturePiece(Pyramid(0,2), player);
    CPPUNIT_ASSERT(!vb.hasATree(player));
    CPPUNIT_ASSERT(!vb.hasATree());
    vb.capturePiece(Pyramid(0,3), player);
    CPPUNIT_ASSERT(vb.hasATree(player));
    CPPUNIT_ASSERT(vb.hasATree());
    // solid-colour tree
}
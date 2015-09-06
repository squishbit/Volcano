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

void VolcanoBoardTest::testChangePlayer() {
    VolcanoBoard volcanoBoard;
    volcanoBoard.changePlayer();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void VolcanoBoardTest::testErupt() {
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
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
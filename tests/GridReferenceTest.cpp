/*
 * File:   GridReferenceTest.cpp
 * Author: squish
 *
 * Created on Aug 12, 2015, 9:42:47 PM
 */

#include "GridReferenceTest.h"
#include "../GridReference.h"


CPPUNIT_TEST_SUITE_REGISTRATION(GridReferenceTest);

GridReferenceTest::GridReferenceTest() {
}

GridReferenceTest::~GridReferenceTest() {
}

void GridReferenceTest::setUp() {
}

void GridReferenceTest::tearDown() {
}

void GridReferenceTest::testGetAdjacent_Center() {
    GridReference gridReference(2,2);
    std::vector<GridReference> result = gridReference.getAdjacent();
    CPPUNIT_ASSERT(result.size() == 8);
}

void GridReferenceTest::testGetValidMoves_Side() {
    GridReference gridReference(4,2);
    std::vector<Direction> result = gridReference.getValidMoves();
    CPPUNIT_ASSERT(result.size() == 5);
}

void GridReferenceTest::testCanMove_Center() {
    GridReference gridReference(3, 4);
    CPPUNIT_ASSERT(gridReference.canMove(1, 0));
    CPPUNIT_ASSERT(!gridReference.canMove(1, 1)); // leaves board
}

void GridReferenceTest::testCanMove_LowerBound() {
    GridReference gridReference(0, 0);
    CPPUNIT_ASSERT(gridReference.canMove(1, 0));
    CPPUNIT_ASSERT(gridReference.canMove(1, 1)); 
    CPPUNIT_ASSERT(!gridReference.canMove(-1, -1)); // leaves board
}

void GridReferenceTest::testCanMove_UpperBound() {
    GridReference gridReference(4, 4);
    CPPUNIT_ASSERT(gridReference.canMove(-1, 0));
    CPPUNIT_ASSERT(gridReference.canMove(-1, -1)); 
    CPPUNIT_ASSERT(!gridReference.canMove(-1, 1)); // leaves board
}

void GridReferenceTest::testGetDirection() {
    GridReference to(4,2);
    GridReference from(3,3);
    Direction d = from.getDirection(to);
    CPPUNIT_ASSERT(d.ns == 1);
    CPPUNIT_ASSERT(d.ew == -1);
}

void GridReferenceTest::testIsAdjacent() {
    GridReference gr(0,0);
    GridReference adj(1,0);
    GridReference nonadj(1,3);
    CPPUNIT_ASSERT(gr.isAdjacent(adj));
    CPPUNIT_ASSERT(!gr.isAdjacent(nonadj));
}

void GridReferenceTest::testMove_int() {
    GridReference gridReference(3,2);
    gridReference.move(-1, 1);
    CPPUNIT_ASSERT(gridReference.row == 2);
    CPPUNIT_ASSERT(gridReference.col == 3);
}

void GridReferenceTest::testMove_Dir() {
    GridReference gridReference(3,2);
    gridReference.move(Direction(-1, 1));
    CPPUNIT_ASSERT(gridReference.row == 2);
    CPPUNIT_ASSERT(gridReference.col == 3);
}

void GridReferenceTest::testMoved_int() {
    GridReference gridReference(0,0);
    GridReference result = gridReference.moved(1, 1);
    CPPUNIT_ASSERT(result.row == 1);
    CPPUNIT_ASSERT(result.col == 1);
}

void GridReferenceTest::testMoved_Dir() {
    GridReference gridReference(0,0);
    GridReference result = gridReference.moved(Direction(1, 1));
    CPPUNIT_ASSERT(result.row == 1);
    CPPUNIT_ASSERT(result.col == 1);
}

void GridReferenceTest::testNumber() {
    GridReference gridReference(17);
    unsigned int result = gridReference.number();
    CPPUNIT_ASSERT(result == 17);
}


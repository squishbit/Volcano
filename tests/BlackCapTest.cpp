/*
 * File:   BlackCapTest.cpp
 * Author: squish
 *
 * Created on Aug 12, 2015, 12:01:19 AM
 */

#include <set>

#include "BlackCapTest.h"
#include "../BlackCaps.h"


CPPUNIT_TEST_SUITE_REGISTRATION(BlackCapTest);

BlackCapTest::BlackCapTest() {
}

BlackCapTest::~BlackCapTest() {
}

void BlackCapTest::setUp() {
}

void BlackCapTest::tearDown() {
}

void BlackCapTest::testInit_Empty() {
    BlackCaps blackCaps = BlackCaps();
    for (unsigned int i = 0; i < 25; i++) {
        CPPUNIT_ASSERT(!blackCaps.hasCap(i));
    }
}

void BlackCapTest::testInit_vector() {
    std::vector<GridReference> v;
    v.push_back(GridReference(0));
    v.push_back(GridReference(4));
    v.push_back(GridReference(24));
    BlackCaps blackCaps(v);

    std::bitset<25> bs = 0;
    bs.set(0);
    bs.set(4);
    bs.set(24);

    for (unsigned int i = 0; i < bs.size(); i++) {
        CPPUNIT_ASSERT(bs.test(i) == blackCaps.hasCap(i));
    }
}

void BlackCapTest::testAddCap_GR() {
    GridReference gr(0);
    BlackCaps blackCaps;
    CPPUNIT_ASSERT(!blackCaps.hasCap(0));
    blackCaps.addCap(gr);
    CPPUNIT_ASSERT(blackCaps.hasCap(0));
}

void BlackCapTest::testAddCap_int() {
    int i = 5;
    BlackCaps blackCaps;
    CPPUNIT_ASSERT(!blackCaps.hasCap(i));
    blackCaps.addCap(i);
    CPPUNIT_ASSERT(blackCaps.hasCap(i));
}

void BlackCapTest::testGetAdjacent_Corner() {
    BlackCaps blackCaps;
    blackCaps.addCap(0);
    std::vector<BlackCaps> result = blackCaps.getAdjacent();
    CPPUNIT_ASSERT(result.size() == 3);
}

void BlackCapTest::testGetAdjacent_CornerMultiple() {
    BlackCaps blackCaps;
    blackCaps.addCap(0);
    blackCaps.addCap(GridReference(0,1));
    blackCaps.addCap(GridReference(1,0));
    std::vector<BlackCaps> result = blackCaps.getAdjacent();
    CPPUNIT_ASSERT(result.size() == 7);
}

void BlackCapTest::testGetAdjacent_Side() {
    BlackCaps blackCaps;
    blackCaps.addCap(GridReference(2,4));
    std::vector<BlackCaps> result = blackCaps.getAdjacent();
    CPPUNIT_ASSERT(result.size() == 5);
}

void BlackCapTest::testGetAdjacent_Center() {
    BlackCaps blackCaps;
    blackCaps.addCap(GridReference(2,2));
    std::vector<BlackCaps> result = blackCaps.getAdjacent();
    CPPUNIT_ASSERT(result.size() == 8);
}

void BlackCapTest::testGetSafeAdjacent_Corner() {
    BlackCaps blackCaps;
    blackCaps.addCap(0);
    std::vector<BlackCaps> result = blackCaps.getSafeAdjacent();
    CPPUNIT_ASSERT(result.size() == 0);
}

void BlackCapTest::testGetSafeAdjacent_CanMove() {
    BlackCaps blackCaps;
    blackCaps.addCap(GridReference(1,2));
    std::vector<BlackCaps> result = blackCaps.getSafeAdjacent();
    CPPUNIT_ASSERT(result.size() == 3);
}

void BlackCapTest::testGetAllSafeReachable_CantMove() {
    BlackCaps blackCaps;
    blackCaps.addCap(GridReference(0,0));
    blackCaps.addCap(GridReference(0,4));
    blackCaps.addCap(GridReference(4,4));
    blackCaps.addCap(GridReference(4,0));
    std::set<BlackCaps> result = blackCaps.getAllSafeReachable();
    CPPUNIT_ASSERT(result.size() == 1);
}

void BlackCapTest::testGetAllSafeReachable_CornerStart() {
    BlackCaps blackCaps;
    blackCaps.addCap(GridReference(0,0));
    blackCaps.addCap(GridReference(0,1));
    blackCaps.addCap(GridReference(0,2));
    blackCaps.addCap(GridReference(1,0));
    blackCaps.addCap(GridReference(2,0));
    std::set<BlackCaps> result = blackCaps.getAllSafeReachable();
    CPPUNIT_ASSERT(result.size() == 3);
}

void BlackCapTest::testGetGridReferences() {
    std::set<int> s;
    s.insert(5);
    s.insert(7);
    s.insert(0);
    s.insert(13);
    s.insert(24);
    BlackCaps blackCaps;
    std::set<int>::iterator sIter;
    for (sIter = s.begin(); sIter != s.end(); sIter++) {
        blackCaps.addCap(*sIter);
    }
    std::vector<GridReference> result = blackCaps.getGridReferences();
    std::vector<GridReference>::iterator vIter;
    for (vIter = result.begin(); vIter != result.end(); vIter++) {
        CPPUNIT_ASSERT(s.count(vIter->number()));
    }
}

void BlackCapTest::testHasCap_int() {
    BlackCaps blackCaps;
    blackCaps.addCap(7);
    CPPUNIT_ASSERT(blackCaps.hasCap(7));
    CPPUNIT_ASSERT(!blackCaps.hasCap(9));
}

void BlackCapTest::testHasCap_GR() {
    BlackCaps blackCaps;
    blackCaps.addCap(9);
    CPPUNIT_ASSERT(blackCaps.hasCap(GridReference(9)));
    CPPUNIT_ASSERT(!blackCaps.hasCap(GridReference(17)));
}

void BlackCapTest::testRemoveCap_int() {
    std::vector<GridReference> v;
    v.push_back(GridReference(5));
    BlackCaps blackCaps(v);
    CPPUNIT_ASSERT(blackCaps.hasCap(5));
    blackCaps.removeCap(5);
    CPPUNIT_ASSERT(!blackCaps.hasCap(5));
}

void BlackCapTest::testRemoveCap_GR() {
    std::vector<GridReference> v;
    GridReference gr(5);
    v.push_back(gr);
    BlackCaps blackCaps(v);
    CPPUNIT_ASSERT(blackCaps.hasCap(gr));
    blackCaps.removeCap(gr);
    CPPUNIT_ASSERT(!blackCaps.hasCap(gr));
}

void BlackCapTest::testCanMoveCap_Cardinal() {
    GridReference from(0); //top corner
    BlackCaps blackCaps;
    CPPUNIT_ASSERT(!blackCaps.canMoveCap(from, Direction(1,1)));
    blackCaps.addCap(from);
    CPPUNIT_ASSERT(blackCaps.canMoveCap(from, Direction(1,1)));
    CPPUNIT_ASSERT(!blackCaps.canMoveCap(from, Direction(-1,-1)));
}

void BlackCapTest::testCanMoveCap_Absolute() {
    GridReference from(0);
    GridReference adj(1);
    GridReference nonAdj(24);
    BlackCaps blackCaps;
    CPPUNIT_ASSERT(!blackCaps.canMoveCap(from, adj));
    blackCaps.addCap(from);
    CPPUNIT_ASSERT(blackCaps.canMoveCap(from, adj));
    CPPUNIT_ASSERT(!blackCaps.canMoveCap(from, nonAdj));
}

void BlackCapTest::testCanMoveCapSafely_Cardinal() {
    GridReference from(0,1);
    BlackCaps blackCaps;
    blackCaps.addCap(from);
    // can move safely
    CPPUNIT_ASSERT(blackCaps.canMoveCapSafely(from, Direction(0, -1)));
    // can move but not safely
    CPPUNIT_ASSERT(!blackCaps.canMoveCapSafely(from, Direction(1, 1)));
    // can't move (leaves board)
    CPPUNIT_ASSERT(!blackCaps.canMoveCapSafely(from, Direction(-1, -1)));
}

void BlackCapTest::testCanMoveCapSafely_Absolute() {
    GridReference from(0,1);
    BlackCaps blackCaps;
    blackCaps.addCap(from);
    // can move safely
    CPPUNIT_ASSERT(blackCaps.canMoveCapSafely(from, from.moved(0, -1)));
    // can move but not safely
    CPPUNIT_ASSERT(!blackCaps.canMoveCapSafely(from, from.moved(1, 1)));
    // can't move (not adjacent)
    CPPUNIT_ASSERT(!blackCaps.canMoveCapSafely(from, GridReference(3, 3)));
}

void BlackCapTest::testMoveCap_Absolute() {
    GridReference from(0);
    GridReference to(1);
    BlackCaps blackCaps;
    blackCaps.addCap(from);
    CPPUNIT_ASSERT(blackCaps.hasCap(from));
    CPPUNIT_ASSERT(!blackCaps.hasCap(to));
    blackCaps.moveCap(from, to);
    CPPUNIT_ASSERT(!blackCaps.hasCap(from));
    CPPUNIT_ASSERT(blackCaps.hasCap(to));
}

void BlackCapTest::testMoveCap_Cardinal() {
    GridReference from(2, 2);
    Direction d(-1, -1);
    BlackCaps blackCaps;
    blackCaps.addCap(from);
    CPPUNIT_ASSERT(blackCaps.hasCap(from));
    blackCaps.moveCap(from, d);
    CPPUNIT_ASSERT(!blackCaps.hasCap(from));
    CPPUNIT_ASSERT(blackCaps.hasCap(GridReference(1,1)));
}

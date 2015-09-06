/*
 * File:   GridReferenceTest.h
 * Author: squish
 *
 * TODO: test canMove with Direction class input instead of int.
 *            getAdjacent with corner/side
 * 
 * Created on Aug 12, 2015, 9:42:46 PM
 */

#ifndef GRIDREFERENCETEST_H
#define	GRIDREFERENCETEST_H

#include <cppunit/extensions/HelperMacros.h>

class GridReferenceTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(GridReferenceTest);

    CPPUNIT_TEST(testGetAdjacent_Center);
    CPPUNIT_TEST(testGetValidMoves_Side);
    CPPUNIT_TEST(testCanMove_Center);
    CPPUNIT_TEST(testCanMove_LowerBound);
    CPPUNIT_TEST(testCanMove_UpperBound);
    CPPUNIT_TEST(testGetDirection);
    CPPUNIT_TEST(testIsAdjacent);
    CPPUNIT_TEST(testMove_int);
    CPPUNIT_TEST(testMove_Dir);
    CPPUNIT_TEST(testMoved_int);
    CPPUNIT_TEST(testMoved_Dir);
    CPPUNIT_TEST(testNumber);

    CPPUNIT_TEST_SUITE_END();

public:
    GridReferenceTest();
    virtual ~GridReferenceTest();
    void setUp();
    void tearDown();

private:
    void testGetAdjacent_Center();
    void testGetValidMoves_Side();
    void testCanMove_Center();
    void testCanMove_LowerBound();
    void testCanMove_UpperBound();
    void testGetDirection();
    void testIsAdjacent();
    void testMove_int();
    void testMove_Dir();
    void testMoved_int();
    void testMoved_Dir();
    void testNumber();

};

#endif	/* GRIDREFERENCETEST_H */


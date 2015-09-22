/*
 * File:   BlackCapTest.h
 * Author: squish
 *
 * Created on Aug 12, 2015, 12:01:19 AM
 */

#ifndef BLACKCAPTEST_H
#define	BLACKCAPTEST_H

#include <cppunit/extensions/HelperMacros.h>

class BlackCapTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(BlackCapTest);

    CPPUNIT_TEST(testInit_vector);
    CPPUNIT_TEST(testInit_Empty);
    CPPUNIT_TEST(testAddCap_GR);
    CPPUNIT_TEST(testAddCap_int);
    CPPUNIT_TEST(testGetAdjacent_Corner);
    CPPUNIT_TEST(testGetAdjacent_CornerMultiple);
    CPPUNIT_TEST(testGetAdjacent_Side);
    CPPUNIT_TEST(testGetAdjacent_Center);
    CPPUNIT_TEST(testGetGridReferences);
    CPPUNIT_TEST(testGetSafeAdjacent_Corner);
    CPPUNIT_TEST(testGetSafeAdjacent_CanMove);
    CPPUNIT_TEST(testGetAllSafeReachable_Empty);
    CPPUNIT_TEST(testGetAllSafeReachable_CantMove);
    CPPUNIT_TEST(testGetAllSafeReachable_CornerStart);
    CPPUNIT_TEST(testHasCap_int);
    CPPUNIT_TEST(testHasCap_GR);
    CPPUNIT_TEST(testRemoveCap_int);
    CPPUNIT_TEST(testRemoveCap_GR);
    CPPUNIT_TEST(testCanMoveCap_Cardinal);
    CPPUNIT_TEST(testCanMoveCap_Absolute);
    CPPUNIT_TEST(testCanMoveCapSafely_Cardinal);
    CPPUNIT_TEST(testCanMoveCapSafely_Absolute);
    CPPUNIT_TEST(testMoveCap_Absolute);
    CPPUNIT_TEST(testMoveCap_Cardinal);

    CPPUNIT_TEST_SUITE_END();

public:
    BlackCapTest();
    virtual ~BlackCapTest();
    void setUp();
    void tearDown();

private:
    void testInit_vector();
    void testInit_Empty();
    void testAddCap_int();
    void testAddCap_GR();
    void testGetAdjacent_Corner();
    void testGetAdjacent_CornerMultiple();
    void testGetAdjacent_Side();
    void testGetAdjacent_Center();
    void testGetSafeAdjacent_Corner();
    void testGetSafeAdjacent_CanMove();
    void testGetAllSafeReachable_CantMove();
    void testGetAllSafeReachable_Empty();
    void testGetAllSafeReachable_CornerStart();
    void testGetGridReferences();
    void testHasCap_int();
    void testHasCap_GR();
    void testRemoveCap_int();
    void testRemoveCap_GR();
    void testCanMoveCap_Cardinal();
    void testCanMoveCap_Absolute();
    void testCanMoveCapSafely_Cardinal();
    void testCanMoveCapSafely_Absolute();
    void testMoveCap_Absolute();
    void testMoveCap_Cardinal();

};

#endif	/* BLACKCAPTEST_H */


/*
 * File:   VolcanoBoardTest.h
 * Author: squish
 *
 * Created on 15/08/2015, 4:23:56 PM
 */

#ifndef VOLCANOBOARDTEST_H
#define	VOLCANOBOARDTEST_H

#include <cppunit/extensions/HelperMacros.h>

class VolcanoBoardTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(VolcanoBoardTest);

    CPPUNIT_TEST(testCalculateScore_SolidPyramid);
    CPPUNIT_TEST(testCalculateScore_SolidPyramid_Remainders);
    CPPUNIT_TEST(testCalculateScore_MixedPyramid);
    CPPUNIT_TEST(testCalculateScore_MixedPyramid_Remainders);
    CPPUNIT_TEST(testCalculateScore_AllOfTheAbove);
    CPPUNIT_TEST(testCalculateScore_NothingConnects);
    CPPUNIT_TEST(testCanCapturePiece);
    CPPUNIT_TEST(testErupt);
    CPPUNIT_TEST(testErupt_diffBlackCaps);
    CPPUNIT_TEST(testErupt_blackCap);
    CPPUNIT_TEST(testErupt_offBoard);
    CPPUNIT_TEST(testErupt_emptyStack);
    CPPUNIT_TEST(testIsGameOver_p1);
    CPPUNIT_TEST(testIsGameOver_p2);
    CPPUNIT_TEST(testHasATree_p1);
    CPPUNIT_TEST(testHasATree_p2);

    CPPUNIT_TEST_SUITE_END();

public:
    VolcanoBoardTest();
    virtual ~VolcanoBoardTest();
    void setUp();
    void tearDown();

private:
    void testCalculateScore_SolidPyramid();
    void testCalculateScore_SolidPyramid_Remainders();
    void testCalculateScore_MixedPyramid();
    void testCalculateScore_MixedPyramid_Remainders();
    void testCalculateScore_AllOfTheAbove();
    void testCalculateScore_NothingConnects();
    void testCanCapturePiece();
    void testErupt();
    void testErupt_diffBlackCaps();
    void testErupt_blackCap();
    void testErupt_offBoard();
    void testErupt_emptyStack();
    void testIsGameOver_p1();
    void testIsGameOver_p2();
    void testHasATree_p1();
    void testHasATree_p2();

};

#endif	/* VOLCANOBOARDTEST_H */


/*
 * File:   PyramidTest.h
 * Author: squish
 *
 * Created on Aug 11, 2015, 11:34:42 PM
 */

#ifndef PYRAMIDTEST_H
#define	PYRAMIDTEST_H

#include <cppunit/extensions/HelperMacros.h>

class PyramidTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(PyramidTest);

    CPPUNIT_TEST(testGetColour);
    CPPUNIT_TEST(testGetPips);

    CPPUNIT_TEST_SUITE_END();

public:
    PyramidTest();
    virtual ~PyramidTest();
    void setUp();
    void tearDown();

private:
    void testGetColour();
    void testGetPips();

};

#endif	/* PYRAMIDTEST_H */


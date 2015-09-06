/*
 * File:   PyramidTest.cpp
 * Author: squish
 *
 * Created on Aug 11, 2015, 11:34:42 PM
 */

#include "PyramidTest.h"
#include "../Pyramid.h"

CPPUNIT_TEST_SUITE_REGISTRATION(PyramidTest);

PyramidTest::PyramidTest() {
}

PyramidTest::~PyramidTest() {
}

void PyramidTest::setUp() {
}

void PyramidTest::tearDown() {
}

void PyramidTest::testGetColour() {
    unsigned int colour = 3;
    unsigned int pips = 1;
    Pyramid pyramid(colour, pips);
    unsigned int result = pyramid.getColour();

    CPPUNIT_ASSERT(result == colour);
}

void PyramidTest::testGetPips() {
    unsigned int colour = 3;
    unsigned int pips = 1;
    Pyramid pyramid(colour, pips);
    
    unsigned int result = pyramid.getPips();
    CPPUNIT_ASSERT(result == pips);
}

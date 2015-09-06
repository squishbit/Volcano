/* 
 * File:   Pyramid.cpp
 * Author: squish
 * 
 * Created on August 11, 2015, 11:15 PM
 */

#include <stdexcept>

#include "Pyramid.h"

#define COLOURS 5
#define PIPS 3


Pyramid::Pyramid(unsigned int colour, unsigned int pips) {
    if (colour >= COLOURS || pips > PIPS || pips <= 0) {
        throw std::invalid_argument("Pyramid constructor: colour must be 0-5, pips must be 1-3");
    }

    value = colour;
    value <<= 2;
    value |= pips;
}

unsigned int Pyramid::getColour() const {
    return value >> 2;
}

unsigned int Pyramid::getPips() const {
    return value & 0x03;
}


std::ostream& operator<< (std::ostream & out, const Pyramid& p) {
    unsigned int pips = p.getPips();
    out << "\033[1;" << 31+p.getColour() << "m";
    for (unsigned int i = 1; i <= PIPS; i++) {
        if (i <= pips) {
            out << '*';
        } else {
            out << ' ';
        }
    }
    out << "\033[0m"; // << 31+p.getColour() << "m";
    return out ;
}

bool operator== (const Pyramid &p1, const Pyramid &p2) {
    return p1.value == p2.value;
}
bool operator!= (const Pyramid &p1, const Pyramid &p2) {
    return p1.value != p2.value;
}
bool operator<  (const Pyramid &p1, const Pyramid &p2) {
    return p1.value < p2.value;
}
bool operator<= (const Pyramid &p1, const Pyramid &p2) {
    return p1.value <= p2.value;
}
bool operator>  (const Pyramid &p1, const Pyramid &p2) {
    return p1.value > p2.value;
}
bool operator>= (const Pyramid &p1, const Pyramid &p2) {
    return p1.value >= p2.value;
}

bool comparePips (const Pyramid& first, const Pyramid& second) {
    return (first.getPips() < second.getPips());
}

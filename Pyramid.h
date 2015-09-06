/* 
 * File:   Pyramid.h
 * Author: squish
 *
 * Defines a class representing an IceHouse Pyramid,
 * characterised with a colour and a number of pips.
 * 
 * Created on August 11, 2015, 11:15 PM
 */

#ifndef PYRAMID_H
#define	PYRAMID_H

#include <iostream>
#include <stdint.h>


class Pyramid
{
    public:
        Pyramid(unsigned int colour, unsigned int pips);
        unsigned int getColour() const;
        unsigned int getPips() const;

        friend bool operator== (const Pyramid &p1, const Pyramid &p2);
        friend bool operator!= (const Pyramid &p1, const Pyramid &p2);
        friend bool operator<  (const Pyramid &p1, const Pyramid &p2);
        friend bool operator<= (const Pyramid &p1, const Pyramid &p2);
        friend bool operator>  (const Pyramid &p1, const Pyramid &p2);
        friend bool operator>= (const Pyramid &p1, const Pyramid &p2);
        friend std::ostream& operator<<(std::ostream&, const Pyramid&);
    protected:
    private:
        uint8_t value;
};

bool comparePips (const Pyramid&, const Pyramid&);

#endif	/* PYRAMID_H */
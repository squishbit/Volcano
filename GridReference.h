/* 
 * File:   GridReference.h
 * Author: squish
 *
 * Created on August 11, 2015, 11:29 PM
 */

#ifndef GRIDREFERENCE_H
#define	GRIDREFERENCE_H

#include <stdint.h>
#include <vector>

#define WIDTH 5

class Direction
{
    public:
        Direction() : ns(0), ew(0) {}
        /**
         * @param ns_ should be between -1 and 1
         * @param ew_ should be between -1 and 1
         */
        Direction(int ns_, int ew_) : ns(ns_), ew(ew_) {}
        Direction(const Direction& orig) : ns(orig.ns), ew(orig.ew) {}
        int8_t ns;
        int8_t ew;
};

class GridReference
{
    public:
        GridReference(uint8_t r, uint8_t c) : row(r), col(c) {}
        GridReference(unsigned int n) { row = n/WIDTH; col = n%WIDTH; }
        GridReference(const GridReference& orig) : row(orig.row), col(orig.col) {}
        unsigned int number() const { return row*WIDTH + col; }
        bool canMove(int ns, int ew) const;
        bool canMove(const Direction& d) const;
        bool isAdjacent(const GridReference& gr) const;
        Direction getDirection(const GridReference& to) const {
            return Direction(to.row - row, to.col - col);
        }
        void move(int ns, int ew) { row += ns; col += ew; }
        void move(const Direction& d) { move(d.ns, d.ew); }
        GridReference moved(int ns, int ew) const { return GridReference(row+ns, col+ew); }
        GridReference moved(const Direction& d) const { return moved(d.ns, d.ew); }
        std::vector<GridReference> getAdjacent() const;
        std::vector<Direction> getValidMoves() const;
        int8_t row;
        int8_t col;
};

#endif	/* GRIDREFERENCE_H */


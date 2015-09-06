/* 
 * File:   GridReference.cpp
 * Author: squish
 * 
 * Created on August 11, 2015, 11:29 PM
 */

#include "GridReference.h"

/**
 * ns and ew should be +-1 or 0
 * @param ns
 * @param ew
 * @return 
 */
bool GridReference::canMove(int ns, int ew) const {
    return (((row + ns) >= 0) && ((row + ns) < WIDTH) &&
            ((col + ew) >= 0) && ((col + ew) < WIDTH));
}

bool GridReference::canMove(const Direction& d) const {
    return (canMove(d.ns, d.ew));
}

bool GridReference::isAdjacent(const GridReference& gr) const {
    int ns = gr.row - row;
    int ew = gr.col - col;
    return ((ns <= 1) &&(ns >= -1) &&
        (ew <= 1) && (ew >= -1));
}

std::vector<GridReference> GridReference::getAdjacent() const {
    std::vector<GridReference> ret;
    for ( int ns = -1 ; ns <= 1 ; ns++ ) {
        for ( int ew = -1 ;  ew <= 1 ; ew++ ) {
            if ( ns == 0 && ew == 0) continue;
            if ( canMove(ns, ew) ) {
                ret.push_back(moved(ns, ew));
            }
        }
    }
    return ret;
}

/**
 * Where valid means "doesnt leave the game board"
 * @return 
 */
std::vector<Direction> GridReference::getValidMoves() const {
    std::vector<Direction> ret;
    for ( int ns = -1 ; ns <= 1 ; ns++ ) {
        for ( int ew = -1 ;  ew <= 1 ; ew++ ) {
            if ( ns == 0 && ew == 0) continue;
            if ( canMove(ns, ew) ) {
                ret.push_back(Direction(ns, ew));
            }
        }
    }
    return ret;
}
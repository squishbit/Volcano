/* 
 * File:   Minimax.cpp
 * Author: squish
 * 
 * Created on 17 August 2015, 8:30 PM
 */

#include "Minimax.h"
#include "VolcanoBoard.h"

Minimax::Minimax(const Minimax& orig) {
}

void Minimax::doMinimax(VolcanoBoard vb) {
    if (testEndCondition(vb)) {
        // return score (take score function?)
    }
    
    // get all possible moves.
    //      score by calling doMinimax recursively?
    
    // if p1, return max scoring move
    // if p2, return min scoring move
}

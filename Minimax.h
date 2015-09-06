/* 
 * File:   Minimax.h
 * Author: squish
 *
 * Created on 17 August 2015, 8:30 PM
 */

#ifndef MINIMAX_H
#define	MINIMAX_H

#include "VolcanoBoard.h"

class Minimax {
public:
    Minimax(bool (*endCondFunc)(const VolcanoBoard&)) : endCondition(endCondFunc) {}
    Minimax(const Minimax& orig);
    void doMinimax();
    bool testEndCondition(const VolcanoBoard& vb) { return this->endCondition(vb); }
private:
    bool (*endCondition)(const VolcanoBoard&);
};


#endif	/* MINIMAX_H */


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
    Minimax(bool (*endCondFunc)(const VolcanoBoard&), int (*scoreFunc)(const VolcanoBoard&)) : endCondition(endCondFunc), getScore(scoreFunc) {}
    Minimax(const Minimax& orig);
    int doMinimax(std::vector<VolcanoBoard>& res, const VolcanoBoard& vb, int depth);
    bool testEndCondition(const VolcanoBoard& vb) { return this->endCondition(vb); }
private:
    bool (*endCondition)(const VolcanoBoard&);
    int (*getScore)(const VolcanoBoard&);
};


#endif	/* MINIMAX_H */


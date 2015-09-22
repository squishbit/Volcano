/* 
 * File:   main.cpp
 * Author: squish
 *
 * Created on August 11, 2015, 11:14 PM
 */

#include <cstdlib>
#include <queue>
#include <list>
#include <bitset>

#include "Pyramid.h"
#include "BlackCaps.h"
#include "GridReference.h"
#include "VolcanoBoard.h"

#include "Minimax.h"

using namespace std;

bool tmpGameOverFunc (const VolcanoBoard& vb) {
    // return vb.hasATree();
    return (vb.calculateScore(1) >= 2 || vb.calculateScore(0) >= 2); // either player has score 2
}

int tmpScoreFunc (const VolcanoBoard& vb) {
    // curr player's score - opponents score
    return vb.calculateScore() - vb.calculateScore(!vb.getPlayer());
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    Minimax minmax(&tmpGameOverFunc, &tmpScoreFunc);
    std::vector<VolcanoBoard> res;
    VolcanoBoard vb;
    vb.init();
    minmax.doMinimax(res, vb, 2);
    cout << res.size() << endl;
    cout << res.back() << endl;
    
    //cout << "minimax: " << minmax.testEndCondition(vb) << endl;
    
    
    //VolcanoBoard vb;
    //cout << vb << endl;
    //vb.erupt(GridReference(0,0), Direction(1,0));
    //cout << vb << endl;

    
    /*BlackCaps blackCaps;
    blackCaps.addCap(GridReference(2,0));
    blackCaps.addCap(GridReference(0,2));
    std::set<BlackCaps> result = blackCaps.getAllSafeReachable();
    cout << "length of result: " << result.size() << endl;
    std::set<BlackCaps>::iterator resIter;
    for (resIter = result.begin(); resIter != result.end(); resIter++) {
        cout << *resIter << endl;
    }*/
   
    /*bool player = 0;
    VolcanoBoard volcanoBoard;
    volcanoBoard.capturePiece(Pyramid(3,1), player);
    volcanoBoard.capturePiece(Pyramid(3,2), player);
    volcanoBoard.capturePiece(Pyramid(3,3), player);
    volcanoBoard.capturePiece(Pyramid(2,2), player);
    volcanoBoard.capturePiece(Pyramid(3,2), player);
    volcanoBoard.capturePiece(Pyramid(1,2), player);
    volcanoBoard.capturePiece(Pyramid(0,3), player);
    volcanoBoard.capturePiece(Pyramid(0,2), player);
    volcanoBoard.capturePiece(Pyramid(0,1), player);
    cout << volcanoBoard << endl;
    int result = volcanoBoard.calculateScore(player);
    cout << result << endl;*/
    
    return 0;
}


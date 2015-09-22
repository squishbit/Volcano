/* 
 * File:   Minimax.cpp
 * Author: squish
 * 
 * Created on 17 August 2015, 8:30 PM
 */

#include "Minimax.h"
#include "VolcanoBoard.h"

// highest possible score is <175
#define MAX_SCORE 1000

Minimax::Minimax(const Minimax& orig) {
} // TODO ??

int Minimax::doMinimax(std::vector<VolcanoBoard>& res, const VolcanoBoard& vb, int depth) {
    VolcanoBoard currVb, bestVb;
    std::vector<VolcanoBoard> currList, bestList;
    depth--;

    bool touched = false;
    int bestScore = MAX_SCORE;
    if (vb.isFirstPlayer()) {
        bestScore = -bestScore;
    }
    int currScore = 0;

    // get all possible moves.
    VolcanoMoveGen possibleMoves(vb);

    while (!possibleMoves.isEnd()) {
        currVb = *possibleMoves;
        if (testEndCondition(vb) || depth <= 0) {
            // game over, get score
            currScore = getScore(vb);
        } else {
            // score by calling doMinimax recursively
            currVb.changePlayer();
            currScore = doMinimax(currList, currVb, depth);
        }
        if (!vb.isFirstPlayer()) {
            currScore = -currScore;
        }
        if (vb.isFirstPlayer() && currScore > bestScore) {
            // if p1, return max scoring move
            bestScore = currScore;
            bestVb = currVb;
            bestList = currList;
            touched = true;
        } else if (!vb.isFirstPlayer() && currScore < bestScore) {
            // if p2, return min scoring move
            bestScore = currScore;
            bestVb = currVb;
            bestList = currList;
            touched = true;
        }
        possibleMoves++;
    }
    
    if (touched) {
         TODO : curr/bestLists
        
        res.push_back(bestVb);
    } else {
        // raise error
    }
    return bestScore;
    /*
    function minimax(node, depth, maximizingPlayer)
    if depth = 0 or node is a terminal node
        return the heuristic value of node
    
    bestValue := -∞
    for each child of node
        val := minimax(child, depth - 1, FALSE)
        bestValue := max(bestValue, val)
    return -bestValue
    */

}

/*
 * Q: what is my return value?
 * A: Board, vector<Board>, 'Move', or Score? Combination of the above?
 */
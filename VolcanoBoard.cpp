/* 
 * File:   VolcanoBoard.cpp
 * Author: squish
 * 
 * Created on August 11, 2015, 11:31 PM
 */

#include <iostream>

#include "VolcanoBoard.h"

#define PIPS 3
#define COLOURS 5
#define SCORE_SOLID_TREE 7
#define SCORE_MIXED_TREE 5
#define SCORE_SINGLE 1

VolcanoBoard::VolcanoBoard()
{
    player = 0;

    blackCaps = BlackCaps();
    /* TODO toggle black caps on and off
    blackCaps.addCap(GridReference(4,0));
    blackCaps.addCap(GridReference(3,1));
    blackCaps.addCap(GridReference(2,2));
    blackCaps.addCap(GridReference(1,3));
    blackCaps.addCap(GridReference(0,4));*/
    
    for (unsigned int pips = PIPS; pips > 0; pips--) {
        unsigned int colour = 0;
        board[0][0].push_back(Pyramid(colour, pips));
        board[0][1].push_back(Pyramid(colour, pips));
        board[0][2].push_back(Pyramid(colour, pips));
        board[1][0].push_back(Pyramid(colour, pips));
        board[2][0].push_back(Pyramid(colour, pips));

        colour++;
        board[3][0].push_back(Pyramid(colour, pips));
        board[2][1].push_back(Pyramid(colour, pips));
        board[1][1].push_back(Pyramid(colour, pips));
        board[1][2].push_back(Pyramid(colour, pips));
        board[0][3].push_back(Pyramid(colour, pips));

        colour++; // These get black caps
        board[4][0].push_back(Pyramid(colour, pips));
        board[3][1].push_back(Pyramid(colour, pips));
        board[2][2].push_back(Pyramid(colour, pips));
        board[1][3].push_back(Pyramid(colour, pips));
        board[0][4].push_back(Pyramid(colour, pips));

        colour++;
        board[4][1].push_back(Pyramid(colour, pips));
        board[3][2].push_back(Pyramid(colour, pips));
        board[3][3].push_back(Pyramid(colour, pips));
        board[2][3].push_back(Pyramid(colour, pips));
        board[1][4].push_back(Pyramid(colour, pips));

        colour++;
        board[4][2].push_back(Pyramid(colour, pips));
        board[4][3].push_back(Pyramid(colour, pips));
        board[4][4].push_back(Pyramid(colour, pips));
        board[3][4].push_back(Pyramid(colour, pips));
        board[2][4].push_back(Pyramid(colour, pips));
    }
}

void VolcanoBoard::capturePiece(Pyramid p) {
    capturePiece(p, player);
}

/**
 * inserts pieces into stash in sorted order
 * @param py pyramid to capture
 * @param pl player to capture the pyramid for
 */
void VolcanoBoard::capturePiece(Pyramid py, bool pl) {
    std::list<Pyramid>::iterator stashIter = stash[pl].begin();
    while (*stashIter < py) {
        stashIter++;
    }
    stash[pl].insert(stashIter, py);
}

bool VolcanoBoard::canCapturePiece(const Pyramid &p, const GridReference &gr) const {
    const std::vector<Pyramid>& volc = getStack(gr);
    return (volc.back().getPips() == p.getPips());
}

/**
 * Moving the black cap should be handled separately,
 * changing active player should be handled separately.
 * 
 * @param gr which volcano to erupt
 * @param di which direction to erupt in
 * @return whether the eruption occurred
 */
bool VolcanoBoard::erupt(GridReference gr, Direction di) {
    std::vector<Pyramid>& volc = getStack(gr);
    bool hasErupted = false;
    gr.move(di);
    while (!volc.empty() && gr.canMove(di)) {
        gr.move(di);
        if (blackCaps.hasCap(gr)) {
            break;
        }
        if (canCapturePiece(volc.back(), gr)) {
            // if size matches the top pyramid, capture
            capturePiece(volc.back());
        } else {
            // else it lands on that square
            putPyramid(volc.back(), gr);
        }
        volc.pop_back();
        hasErupted = true;
    }
    return hasErupted;
}

/**
 * Score 7 for a solid-colour tree, 5 for mixed,
 *    and 1 for each single piece.
 * Calculates by copying players stash and removing trees
 *    from stash as it finds and scores them.
 * Assumes Stash is sorted in ascending order by colour then pips.
 * 
 * @param player
 * @return 
 */
int VolcanoBoard::calculateScore(bool player) const {
    std::list<Pyramid> stashCopy = stash[player];
    std::list<Pyramid>::iterator stashIter;
    unsigned int currColour = COLOURS; // not a valid colour
    unsigned int currPips = 0;    // not a valid pip count
    unsigned int score = 0;
    std::list<std::list<Pyramid>::iterator> foundPyr; // list of iterators

    // iterate to find solid-colour trees
    stashIter = stashCopy.begin();
    while (stashIter != stashCopy.end()) {
        if (currColour != stashIter->getColour()) {
            // restart with this colour
            currColour = stashIter->getColour();
            currPips = 0;
        }
        if (stashIter->getPips() == (currPips+1)) {
            foundPyr.push_back(stashIter);
            currPips++;
        }
        if (currPips == PIPS) {
            // pop pyramid, score, restart stash iteration
            while (!foundPyr.empty()) {
                stashCopy.erase(foundPyr.front());
                foundPyr.pop_front();
                currPips = 0;
            }
            score += SCORE_SOLID_TREE;
            stashIter = stashCopy.begin();
        } else {
            stashIter++;
        }
    }

    // iterate to find mixed-colour trees
    stashCopy.sort(comparePips);
    currPips = 0;
    foundPyr.clear();
    stashIter = stashCopy.begin();
    while (stashIter != stashCopy.end()) {
        if (stashIter->getPips() == (currPips+1)) {
            foundPyr.push_back(stashIter);
            currPips++;
        }
        if (currPips == PIPS) {
            // pop pyramid, score, restart stash iteration
            while (!foundPyr.empty()) {
                stashCopy.erase(foundPyr.front());
                foundPyr.pop_front();
                currPips = 0;
            }
            score += SCORE_MIXED_TREE;
            stashIter = stashCopy.begin();
        } else {
            stashIter++;
        }
    }

    // score remainder
    score += (stashCopy.size() * SCORE_SINGLE);

    return score;
}

/**
 * Checks if either player has ended the game.
 * 
 * @return true if either player has captured a piece of each colour
 */
bool VolcanoBoard::isGameOver() const {
    return (isGameOver(0) || isGameOver(1)); // players 0 and 1
}

/**
 * Checks for given player if they have ended the game.
 * 
 * @param player 0 or 1
 * @return true if player has captured a piece of each colour
 */
bool VolcanoBoard::isGameOver(bool player) const {
    std::list<Pyramid> stashCopy = stash[player];
    std::list<Pyramid>::iterator stashIter;
    int currColour = -1; // not a valid colour
    
    for (stashIter = stashCopy.begin(); stashIter != stashCopy.end(); stashIter++) {
        if (stashIter->getColour() == (currColour+1)) {
            currColour++;
        } else if (stashIter->getColour() != currColour) {
            // missed a colour, return false
            return false;
        }
    }
    return (currColour == (COLOURS-1));
}

bool VolcanoBoard::hasATree() const {
    return (hasATree(0) || hasATree(1));
}

bool VolcanoBoard::hasATree(bool player) const {
    const std::list<Pyramid> &stashCopy = stash[player];
    std::list<Pyramid>::const_iterator stashIter;
    
    for (unsigned int pips = 1; pips <= PIPS; pips++) {
        // find if player has captured any piece with this number of pips
        bool found = false;
        for (stashIter = stashCopy.begin(); stashIter != stashCopy.end(); stashIter++) {
            if (stashIter->getPips() == pips) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    
    return true;
}

std::ostream& operator<< (std::ostream & out, const VolcanoBoard& vb) {
    out << "---------------------" << std::endl;
    for (int row = 0; row < WIDTH; row++) {
        // get height for this row
        int height = 0;
        for (int x = 0; x < WIDTH; x++) {
            height = std::max(int(vb.board[row][x].size()), height);
        }
        // print row
        for (int subRow = height-1; subRow >= 0; subRow--) {
            for (int col = 0; col < WIDTH; col++) {
                if (vb.blackCaps.hasCap(GridReference(row,col))) {
                    out << "|\033[40m";
                } else {
                    out << "|\033[47m";
                }
                if (subRow < int(vb.board[row][col].size())) {
                    out << vb.board[row][col][subRow];
                } else {
                    out << "   ";
                }
            }
            out << "\033[0m|" << std::endl;
        }
        out << "---------------------" << std::endl;
    }
    
    std::list<Pyramid>::const_iterator stashIter;
    int i = 1;
    for (unsigned int p = 0; p <=1; p++) {
        out << "Player " << p+1 << " stash:" << std::endl;
        for (stashIter = vb.stash[p].begin(); stashIter != vb.stash[p].end(); stashIter++, i++) {
            out << *stashIter;
            if ((i % 5)) {
                out << " ";
            } else {
                out << std::endl;
            }
        }
        out << std::endl;
    }
    return out;
}


/*  defining end game/score functions for minimax?
 
bool isGameOver(const VolcanoBoard& vb) {
    return vb.isGameOver();
}

int score(const VolcanoBoard& vb, bool player) {
    int myScore   = vb.calculateScore(player);
    int yourScore = vb.calculateScore(!player);
    if (myScore > yourScore) {
        return 1;  // win
    } else if (yourScore > myScore) {
        return -1; // lose
    } else {
        return 0;  // draw
    }
}
    
 */
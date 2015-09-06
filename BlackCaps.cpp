/* 
 * File:   BlackCaps.cpp
 * Author: squish
 * 
 * Created on August 11, 2015, 11:26 PM
 */
#include <queue>

#include "BlackCaps.h"

BlackCaps::BlackCaps(std::vector<GridReference> v) {
    value = 0;
    std::vector<GridReference>::iterator iter;
    for (iter = v.begin(); iter != v.end(); ++iter) {
        addCap(*iter);
    }
}

bool BlackCaps::canMoveCap(const GridReference& from, const Direction& to) const {
    return (hasCap(from) &&
            from.canMove(to) &&
            !hasCap(from.moved(to)));
}

bool BlackCaps::canMoveCap(const GridReference& from, const GridReference& to) const {
    return (hasCap(from) &&
            from.isAdjacent(to) &&
            !hasCap(to));
}

/**
 * differs from (gr,gr) version of function:
 *    canMoveCap differs (assumes adjacency, checks if it falls off the board)
 * @param from
 * @param to
 * @return 
 */
bool BlackCaps::canMoveCapSafely(const GridReference& from, const Direction& to) const {
    return (canMoveCap(from, to) &&
            (!from.moved(to).canMove(to) ||
             hasCap(from.moved(to).moved(to))));
}

/**
 * Different to (gr,dir) version of function:
 *    canMoveCap differs (checks adjacency, assumes 'to' is o the board)
 * @param from
 * @param to
 * @return 
 */
bool BlackCaps::canMoveCapSafely(const GridReference& from, const GridReference& to) const {
    Direction d = from.getDirection(to);
    return (canMoveCap(from, to) && // checks adjacency
            (!from.moved(d).canMove(d) ||
             hasCap(from.moved(d).moved(d))));
}

std::vector<BlackCaps> BlackCaps::getAdjacent() const {
    std::vector<BlackCaps> ret = std::vector<BlackCaps>();
    std::vector<GridReference> grThese = getGridReferences();

    for (unsigned int i = 0; i < grThese.size(); i++) {
        // for all black caps
        GridReference grOrig = grThese[i];
        std::vector<GridReference> grAdj = grThese[i].getAdjacent();
        std::vector<GridReference>::iterator grAdjIter;
        for (grAdjIter = grAdj.begin(); grAdjIter != grAdj.end(); ++grAdjIter) {
            // for all adjacent squares
            if (!hasCap(*grAdjIter)) {
                // if adjacent square is empty,
                // update current cap to new square and yield board position
                grThese[i] = *grAdjIter;
                ret.push_back(grThese);
            }
        }
        // reset this cap to orig position
        grThese[i] = grOrig;
    }

    return ret;
}

std::vector<BlackCaps> BlackCaps::getSafeAdjacent() const {
    std::vector<BlackCaps> ret;
    std::vector<GridReference> grThese = getGridReferences();

    for (unsigned int i = 0; i < grThese.size(); i++) {
        // for all black caps
        GridReference grOrig = grThese[i];
        std::vector<Direction> grAdj = grThese[i].getValidMoves();
        std::vector<Direction>::iterator grAdjIter;
        for (grAdjIter = grAdj.begin(); grAdjIter != grAdj.end(); ++grAdjIter) {
            // for all adjacent moves
            if (canMoveCapSafely(grOrig, *grAdjIter)) {
                // if can move without erupting,
                // update current cap to new square and yield board position
                grThese[i] = grOrig.moved(*grAdjIter);
                ret.push_back(grThese);
            }
        }
        // reset this cap to orig position
        grThese[i] = grOrig;
    }

    return ret;
}

std::set<BlackCaps> BlackCaps::getAllSafeReachable() const {
    std::set<BlackCaps> explored;
    std::queue<BlackCaps> que;
    BlackCaps curr;
    std::vector<BlackCaps> currAdj;
    std::vector<BlackCaps>::iterator currIter;
    
    que.push(*this);
    while (!que.empty()) {
        curr = que.front();
        que.pop();
        if (explored.count(curr)) {
            continue;
        }
        currAdj = curr.getSafeAdjacent();
        for (currIter = currAdj.begin(); currIter != currAdj.end(); currIter++) {
            que.push(*currIter);
        }
        explored.insert(curr);
    }
    return explored;
}

std::vector<GridReference> BlackCaps::getGridReferences() const{
    std::vector<GridReference> ret = std::vector<GridReference>();
    for (unsigned int i = 0; i < value.size(); i++) {
        if (hasCap(i)) {
            ret.push_back(GridReference(i));
        }
    }
    return ret;
}


/* Friend functions */

bool operator== (const BlackCaps &bc1, const BlackCaps &bc2) {
    return (bc1.value == bc2.value);
}

bool operator!= (const BlackCaps &bc1, const BlackCaps &bc2) {
    return (bc1.value != bc2.value);
}

bool operator< (const BlackCaps &bc1, const BlackCaps &bc2) {
    return (bc1.value.to_ulong() < bc2.value.to_ulong());
}

bool operator> (const BlackCaps &bc1, const BlackCaps &bc2) {
    return (bc1.value.to_ulong() > bc2.value.to_ulong());
}

bool operator<= (const BlackCaps &bc1, const BlackCaps &bc2) {
    return (bc1.value.to_ulong() <= bc2.value.to_ulong());
}

bool operator>= (const BlackCaps &bc1, const BlackCaps &bc2) {
    return (bc1.value.to_ulong() >= bc2.value.to_ulong());
}

std::ostream& operator<< (std::ostream & out, const BlackCaps& bc) {
    for (int i = 0; i < bc.value.size(); i++) {
        if (bc.value.test(i)) {
            out << '*';
        } else {
            out << '_';
        }
        if (!((i+1)%5)) {
            out << std::endl;
        }
    }
    return out;
}

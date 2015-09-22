/* 
 * File:   VolcanoBoard.h
 * Author: squish
 *
 * Created on August 11, 2015, 11:31 PM
 */

#ifndef VOLCANOBOARD_H
#define	VOLCANOBOARD_H

#include <vector>
#include <list>

#include "Pyramid.h"
#include "BlackCaps.h"
#include "GridReference.h"

#define WIDTH 5


class VolcanoBoard {
    public:
        VolcanoBoard();
        VolcanoBoard(const VolcanoBoard&);
        void initBlackCaps();
        void initPyramids();
        void init();
        void putPyramid(Pyramid py, GridReference gr) { getStack(gr).push_back(py); }
        void putCap(const GridReference& gr) { blackCaps.addCap(gr); }
        bool erupt(GridReference, Direction);
        bool willErupt(GridReference gr, Direction di) const { return willErupt(gr, di, blackCaps); }
        bool willErupt(GridReference, Direction, const BlackCaps&) const;
        bool getPlayer() const { return player; }
        bool isFirstPlayer() const { return !player; }
        void changePlayer() { player = !player; }
        void capturePiece(Pyramid p) { capturePiece(p, player); }
        void capturePiece(Pyramid py, bool player);
        bool canCapturePiece(const Pyramid&, const GridReference&) const;
        int calculateScore() const { return calculateScore(player); }
        int calculateScore(bool player) const;
        bool isGameOver() const;
        bool isGameOver(bool player) const;
        bool hasATree() const;
        bool hasATree(bool player) const;
        std::vector<Pyramid>& getStack(GridReference gr) { return board[gr.row][gr.col]; }
        const std::vector<Pyramid>& getStack(GridReference gr) const { return board[gr.row][gr.col]; }
        friend std::ostream& operator<<(std::ostream&, const VolcanoBoard&);
    protected:
    private:
        std::vector<Pyramid> board[WIDTH][WIDTH];
        BlackCaps blackCaps;
        bool player;
        std::list<Pyramid> stash[2];
};

class VolcanoMoveGen {
    public:
        VolcanoMoveGen(const VolcanoBoard& vb);
        VolcanoMoveGen& operator++(int i);
        VolcanoBoard operator* ();
        bool isEnd() const { return isDone; }
    private:
        void step();
        void findNextValid();

        const VolcanoBoard& orig;
        bool isDone;
        int currRow, currCol;
        std::vector<Direction> dirsFromHere;
        std::vector<Direction>::iterator currDir, lastDir;
};

#endif	/* VOLCANOBOARD_H */

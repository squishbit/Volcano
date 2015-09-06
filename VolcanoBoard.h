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

class VolcanoBoard
{
    public:
        VolcanoBoard();
        void putPyramid(Pyramid py, GridReference gr) { getStack(gr).push_back(py); }
        bool erupt(GridReference, Direction);
        void changePlayer() { player = !player; }
        void capturePiece(Pyramid p);
        void capturePiece(Pyramid py, bool player);
        bool canCapturePiece(const Pyramid&, const GridReference&) const;
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


#endif	/* VOLCANOBOARD_H */


/* 
 * File:   BlackCaps.h
 * Author: squish
 *
 * Created on August 11, 2015, 11:26 PM
 */

#ifndef BLACKCAPS_H
#define	BLACKCAPS_H

#include <vector>
#include <set>
#include <bitset>
#include <iostream>

#include "GridReference.h"


class BlackCaps
{
    public:
        BlackCaps() : value(0) {}
        BlackCaps(const BlackCaps& bc) : value(bc.value) {}
        BlackCaps(std::vector<GridReference> v);
        bool any() { return value.any(); }
        bool hasCap(const GridReference& gr) const { return hasCap(gr.number()); }
        bool hasCap(unsigned int n) const { return value.test(n); }
        void addCap(const GridReference& gr) { addCap(gr.number()); }
        void addCap(unsigned int n) { value.set(n); }
        void removeCap(const GridReference& gr) { removeCap(gr.number()); }
        void removeCap(unsigned int n) { value.reset(n); }
        /**
         * canMoveCap(from, to) should evaluate to true,
         *    otherwise cap count may change.
         * @param from hasCap(from) should be true
         * @param to hasCap(from) should be false
         */
        void moveCap(const GridReference& from, const GridReference& to) {
            removeCap(from);
            addCap(to);
        }
        void moveCap(const GridReference& from, const Direction& to) {
            moveCap(from, from.moved(to));
        }
        //bool canMoveCap(const GridReference& from, int ns, int ew) const;
        bool canMoveCap(const GridReference& from, const Direction& to) const;
        bool canMoveCap(const GridReference& from, const GridReference& to) const;
        //bool canMoveCapSafely(const GridReference& from, int ns, int ew) const;
        bool canMoveCapSafely(const GridReference& from, const Direction& to) const;
        bool canMoveCapSafely(const GridReference& from, const GridReference& to) const;
        std::vector<GridReference> getGridReferences() const;
        std::vector<BlackCaps> getAdjacent() const;
        std::set<BlackCaps> getAllSafeReachable() const;
        std::vector<BlackCaps> getSafeAdjacent() const;
        
        friend bool operator== (const BlackCaps &bc1, const BlackCaps &bc2);
        friend bool operator!= (const BlackCaps &bc1, const BlackCaps &bc2);
        friend bool operator< (const BlackCaps &bc1, const BlackCaps &bc2);
        friend bool operator<= (const BlackCaps &bc1, const BlackCaps &bc2);
        friend bool operator> (const BlackCaps &bc1, const BlackCaps &bc2);
        friend bool operator>= (const BlackCaps &bc1, const BlackCaps &bc2);
        friend std::ostream& operator<<(std::ostream&, const BlackCaps&);
    protected:
    private:
        std::bitset<25> value;
};

#endif	/* BLACKCAPS_H */
// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#ifndef __LKMC__LKMC__
#define __LKMC__LKMC__

#include "../KMC/KMC.h"
#include "../Lattice/Lattice.h"
#include "../Lattice/Adatom.h"

class Cartesian2D;

class LKMC : public KMC {
public:
    LKMC();
    ~LKMC();

    std::vector<Adatom<2>*> step();
    void outputStatus();
    void newAdatom(int x, int y);

protected:
    static void grapheneRate(LKMCNode<6,2>* node);
    static void cbnRate(LKMCNode<6,2>* node);
    static void cbnGradientRate(LKMCNode<6,2>* node);
    static double interactionPotential(double R);

private:
    Lattice<Cartesian2D, LKMCNode<6,2>>* m_l;
    std::vector<Adatom<2>*> m_adatoms;
};

#endif // __LKMC__LKMC__

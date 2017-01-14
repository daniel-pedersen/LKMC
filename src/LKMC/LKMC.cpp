// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#include "LKMC.h"
#include "../Lattice/Space.h"
#include "../KMC/random.h"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

#define LATTICE_POINTS 10000
#define PREFACTOR_FREQ 1.0e+13
#define TEMP 1000.0
#define BOLTZMANN_EV 8.6173324e-5

#define GRAPHENE_ENERGY         0.3
#define BORON_NITRIDE_ENERGY    0.2

#define FORCE_FACTOR 3.0
#define BINDING_RADIUS 0.84
#define BINDING_ENERGY (4.0/(BINDING_RADIUS*BINDING_RADIUS*BINDING_RADIUS))

static double energyFactor(double E_ev)
{
    return exp(-E_ev / (BOLTZMANN_EV * TEMP));
}

static double energyToRate(double E_eV)
{
    return PREFACTOR_FREQ * energyFactor(E_eV);
}

static double rateToEnergy(double k)
{
    return -log(k / PREFACTOR_FREQ) * (BOLTZMANN_EV * TEMP);
}

static const double graphene_rate_k = energyToRate(GRAPHENE_ENERGY);
static const double bn_rate_k = energyToRate(BORON_NITRIDE_ENERGY);
//Vector2D u1(1.0, 0.0), u2(0.5, 0.5 * sqrt(3.0));
Vector2D* u[2] = {new Vector2D(0.5 * sqrt(3.0), 0.5), new Vector2D(0.5 * sqrt(3.0), -0.5)};
const Basis<Cartesian2D> latticeBasis(u);

LKMC::LKMC() :
    KMC()
{
	int neighbors[6][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, -1}, {-1, 1}};
	NeighborBasis<6,2> nb(neighbors);
    m_l = new Lattice<Cartesian2D, LKMCNode<6,2>>(latticeBasis, nb, LATTICE_POINTS);
    // m_l->apply(cbnGradientRate);
    m_l->apply(grapheneRate);
}

LKMC::~LKMC()
{
    vector<Adatom<2>*>::iterator it;
    for (it = m_adatoms.begin(); it != m_adatoms.end(); ++it)
        delete *it;
}

vector<Adatom<2>*> LKMC::step()
{
    vector<Adatom<2>*>::iterator it, it2;
    clearRates();
    for (it = m_adatoms.begin(); it != m_adatoms.end(); ++it) {
        LKMCNode<6,2>* activeNode = m_l->getNodeAt((*it)->getPos());
        double potentialAtNode = 0.0, potentialAtSaddle;
        for (it2 = m_adatoms.begin(); it2 != m_adatoms.end(); ++it2) {
            if (it == it2) continue;
            potentialAtNode += interactionPotential(m_l->m_basis.distance((*it)->getPos(), (*it2)->getPos()));
        }
        Cartesian2D::Vector v1, v2;
        for (int i = 0; i < 6; ++i) {
            potentialAtSaddle = 0.0;
            v1 = 0.5 * (m_l->m_basis.transform(activeNode->getPos()) +
                        m_l->m_basis.transform(activeNode->getNeighbor(i)->getPos()));
            for (it2 = m_adatoms.begin(); it2 != m_adatoms.end(); ++it2) {
                if (it == it2) continue;
                v2 = m_l->m_basis.transform((*it2)->getPos());
                potentialAtSaddle += interactionPotential(Cartesian2D::distance(v1, v2));
            }
            double rt1 = activeNode->rate(i);
            double rt2 = energyFactor(potentialAtSaddle - potentialAtNode);
            double rt = rt1 * rt2;
            addRate(rt);
        }
    }
    int s = (int)nextState();
    int el = (int)(s / 6), nb = s % 6;
    m_adatoms[el]->setPos(m_l->getNodeAt(m_adatoms[el]->getPos())->getNeighbor(nb)->getPos());
    return m_adatoms;
}

void LKMC::outputStatus()
{
    vector<Adatom<2>*>::iterator it;
    cout << time() << "\t";
    for (it = m_adatoms.begin(); it != m_adatoms.end(); ++it)
        cout << (*it)->getCoord(0) << "\t" << (*it)->getCoord(1) << "\t";
}

void LKMC::newAdatom(int x, int y)
{
    int* pos = new int[2];
    pos[0] = x;
    pos[1] = y;
    Adatom<2>* a = new Adatom<2>(pos);
    m_adatoms.push_back(a);
    delete[] pos;
}

void LKMC::grapheneRate(LKMCNode<6,2>* node)
{
    for (int i = 0; i < 6; i++)
        node->setRate(i, graphene_rate_k);
}

void LKMC::cbnRate(LKMCNode<6,2>* node)
{
    Vector2D v;
    for (int i = 0; i < 6; i++) {
        v = latticeBasis.transform(node->getNeighbor(i)->getPos());
        if (v[0] < 0)
            node->setRate(i, bn_rate_k);
        else
            node->setRate(i, graphene_rate_k);
    }
}

#define UR1 0.53
#define UR2 0.34
#define UR3 0.1
#define UR4 0.23
#define UR5 0.19
#define UR6 0.2
#define UR7 0.2
#define UR8 0.2
#define UR9 0.3

void LKMC::cbnGradientRate(LKMCNode<6,2>* node)
{
    static const double graphene_junctionE[3][3] = {{0.53, 1.08, 1.3}, {UR1, 0.46, 0.53}, {0.75, 0.32, 0.26}};
    static const double bn_junctionE[3][3] = {{UR2, 0.17, UR3}, {UR4, 0.21, UR5}, {UR6, UR7, UR8}};
    static const double junctionE[3] = {UR9, 0.13, 0.1};

    Vector2D v;
    int nodeX = node->coord(0) + node->coord(1);
    if (-4 < nodeX && nodeX < 4) {
        const double* jrates;

        if      (nodeX > 0) jrates = graphene_junctionE[nodeX - 1];
        else if (nodeX < 0) jrates = bn_junctionE[-nodeX - 1];
        else                jrates = junctionE;

        double E;
        for (int nbrX, i = 0; i < 6; i++) {
            nbrX = node->getNeighbor(i)->coord(0) + node->getNeighbor(i)->coord(1);
            if      (nbrX < nodeX) E = jrates[0];
            else if (nbrX > nodeX) E = jrates[2];
            else                   E = jrates[1];
            node->setRate(i, energyToRate(E));
        }
    } else {
        for (int i = 0; i < 6; i++) {
            v = latticeBasis.transform(node->getNeighbor(i)->getPos());
            if (v[0] < 0)
                node->setRate(i, bn_rate_k);
            else
                node->setRate(i, graphene_rate_k);
        }
    }
}

double LKMC::interactionPotential(double R)
{
    double iR = 1.0 / R, iRSq = iR * iR, iR4 = iRSq * iRSq;
    return FORCE_FACTOR * (iR4 - BINDING_ENERGY * iR);
}

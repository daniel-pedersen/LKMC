// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#ifndef LKMC_LKMCNode_h
#define LKMC_LKMCNode_h

#include "LatticeNode.h"

template <int N, int D>
class LKMCNode : public LatticeNode<N,D> {
public:
    LKMCNode();
    LKMCNode(double rates[N]);

    void setRate(int i, double k);
    inline double rate(int i) { return m_rate[i]; }

private:
    double m_rate[N];
};

template <int N, int D>
LKMCNode<N,D>::LKMCNode() :
    LatticeNode<N,D>()
{
    for (int i = 0; i < N; ++i)
        m_rate[i] = 0.0;
}

template <int N, int D>
LKMCNode<N,D>::LKMCNode(double rates[N]) :
    LatticeNode<N,D>()
{
    for (int i = 0; i < N; ++i)
        m_rate[i] = rates[i];
}

template <int N, int D>
void LKMCNode<N,D>::setRate(int i, double k)
{
    if (i >= 0 && i < N)
        m_rate[i] = k;
}

#endif

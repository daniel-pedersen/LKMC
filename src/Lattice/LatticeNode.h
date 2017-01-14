// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#ifndef __lattice__node__
#define __lattice__node__

#include <cstddef>
#include <cstdlib>

template <int N, int D>
class LatticeNode {
public:
	LatticeNode();
    LatticeNode(const int coord[N]);

    void setCoord(const int coord[N]);
    inline int coord(int i) const { return m_coord[i]; }
    inline const int* getPos() const { return m_coord; }
	void setNeighbor(int k, LatticeNode<N,D>* neighbor);
    LatticeNode<N,D>* getNeighbor(int i);

    static const int nn = N;

protected:
	LatticeNode<N,D>* m_neighbors[N];
    int m_coord[D];
};

template <int N, int D>
LatticeNode<N,D>::LatticeNode()
{
	for (int i = 0; i < N; ++i)
		m_neighbors[i] = NULL;
}

template <int N, int D>
LatticeNode<N,D>::LatticeNode(const int coord[N])
{
    for (int i = 0; i < N; ++i) {
		m_neighbors[i] = NULL;
        m_coord[i] = coord[i];
    }
}

template <int N, int D>
void LatticeNode<N,D>::setCoord(const int coords[N])
{
    for (int i = 0; i < N; ++i)
        m_coord[i] = coords[i];
}

template <int N, int D>
void LatticeNode<N,D>::setNeighbor(int k, LatticeNode<N,D>* neighbor)
{
	if (k >= 0 && k < N)
		m_neighbors[k] = neighbor;
}

template <int N, int D>
LatticeNode<N,D>* LatticeNode<N,D>::getNeighbor(int i)
{
    return m_neighbors[i];
}

#endif

// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#ifndef __lattice__basis__
#define __lattice__basis__

template <class Space>
class Basis {
public:
	inline Basis() { }
    Basis(const Basis& b);
	Basis(typename Space::Vector* basisVectors[Space::dim]);

	void setBaseVector(int i, typename Space::Vector& v);

    typename Space::Vector transform(const int coord[Space::dim]) const;
    double distance(const int p1[Space::dim], const int p2[Space::dim]) const;

private:
	typename Space::Vector m_basisVector[Space::dim];
};

template <int n, int dim>
class NeighborBasis {
public:
	NeighborBasis(const int neighbors[n][dim]);

	const int* operator[](int i);

private:
	int m_nvec[n][dim];
};

template <class Space>
Basis<Space>::Basis(const Basis& b)
{
    for (int i = 0; i < Space::dim; ++i)
		m_basisVector[i] = b.m_basisVector[i];
}

template <class Space>
Basis<Space>::Basis(typename Space::Vector* basisVectors[Space::dim])
{
	for (int i = 0; i < Space::dim; ++i)
		m_basisVector[i] = *basisVectors[i];
}

template <class Space>
void Basis<Space>::setBaseVector(int i, typename Space::Vector& v)
{
	if (i >= 0 && i < Space::dim)
		m_basisVector[i] = v;
}

template <class Space>
typename Space::Vector Basis<Space>::transform(const int coord[Space::dim]) const
{
    typename Space::Vector v;
    for (int i = 0; i < Space::dim; ++i)
        v = v + coord[i] * m_basisVector[i];
    return v;
}

template <class Space>
double Basis<Space>::distance(const int p1[Space::dim], const int p2[Space::dim]) const
{
    return Space::distance(transform(p1), transform(p2));
}

template <int n, int dim>
NeighborBasis<n,dim>::NeighborBasis(const int neighbors[n][dim])
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < dim; ++j)
			m_nvec[i][j] = neighbors[i][j];
}

template <int n, int dim>
const int* NeighborBasis<n,dim>::operator[](int i)
{
	return m_nvec[i];
}

#endif

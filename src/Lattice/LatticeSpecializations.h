// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#ifndef LKMC_LatticeSpecializations_h
#define LKMC_LatticeSpecializations_h

#ifdef LKMC_HEXAGONAL_SPEC

typedef LKMCNode<6,2> HexNode;

template <>
Lattice<Cartesian2D,HexNode>::Lattice(const Basis<Cartesian2D>& basis, const NeighborBasis<2,6>& neighbors, size_t maxSize) :
    m_basis(basis),
    m_neighbors(neighbors)
{
	size_t size = (size_t)sqrt((double)maxSize);
	size_t size_array[2];
    size_array[0] = size;
    size_array[1] = size;
    m_offset[0] = (int)((size % 2) - (size >> 1));
    m_offset[1] = m_offset[0];
	m_lattice = SNArray<HexNode,2>(size_array);
	construct(size);
}

template <>
void Lattice<Cartesian2D,HexNode>::apply(int d, void(*f)(NodeT*))
{
    static int loop[Space::dim];
    if (d == Space::dim - 1) {
        for (loop[d] = 0; loop[d] < m_lattice.size(d); ++loop[d])
            f(m_lattice[loop]);
    } else {
		for (loop[d] = 0; loop[d] < m_lattice.size(d); ++loop[d])
			apply(d + 1, f);
	}
}

#endif // LKMC_HEXAGONAL_SPEC

#endif

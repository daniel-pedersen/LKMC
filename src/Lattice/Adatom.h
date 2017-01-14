// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#ifndef __lattice__adatom__
#define __lattice__adatom__

template <int D>
class Adatom {
public:
    Adatom();
    Adatom(const int latticePos[D]);

    void setPos(const int pos[D]);
    void move(const int dx[D]);

    int getCoord(int i) const;
    const int* getPos() const;

private:
    int m_lattice_pos[D];
};

template <int D>
Adatom<D>::Adatom()
{
    for (int i = 0; i < D; ++i)
        m_lattice_pos[i] = 0;
}

template <int D>
Adatom<D>::Adatom(const int latticePos[D])
{
    for (int i = 0; i < D; ++i)
        m_lattice_pos[i] = latticePos[i];
}

template <int D>
void Adatom<D>::setPos(const int pos[D])
{
    for (int i = 0; i < D; ++i)
        m_lattice_pos[i] = pos[i];
}

template <int D>
void Adatom<D>::move(const int dx[D])
{
    for (int i = 0; i < D; ++i)
        m_lattice_pos[i] += dx[i];
}

template <int D>
int Adatom<D>::getCoord(int i) const
{
    if (i >= 0 && i < D)
        return m_lattice_pos[i];
    return 0;
}

template <int D>
const int* Adatom<D>::getPos() const
{
    return m_lattice_pos;
}

#endif

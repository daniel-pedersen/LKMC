// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#ifndef __lattice__snarray__
#define __lattice__snarray__

#include <vector>

template <class T, int N>
class SNArray {
public:
	SNArray();
	SNArray(const size_t dim[N]);

	T* operator[](int i[N]);
    T* operator[](size_t i);

	inline size_t size(int d) { return m_s[d]; }
    size_t length();

private:
	std::vector<T*> m_x;
	size_t m_s[N];
};

template <class T, int N>
SNArray<T,N>::SNArray()
{
	for (int i = 0; i < N; ++i)
		m_s[i] = 0;
}

template <class T, int N>
SNArray<T,N>::SNArray(const size_t dim[N])
{
	size_t totalSize = 1;
	for (int i = 0; i < N; ++i)
		totalSize *= (m_s[i] = dim[i]);
	m_x.reserve(totalSize);
    for (int i = 0; i < totalSize; ++i)
        m_x[i] = new T();
}

template <class T, int N>
T* SNArray<T,N>::operator[](int i[N])
{
	size_t index = i[N - 1], factor = 1;
	for (int j = N - 2; j >= 0; --j) {
		factor *= m_s[j];
		index += factor * i[j];
	}
    if (index > length())
        return NULL;
	return m_x[index];
}

template <class T, int N>
T* SNArray<T,N>::operator[](size_t i)
{
    if (i > length())
        return NULL;
    return m_x[i];
}

template <class T, int N>
size_t SNArray<T,N>::length()
{
    size_t l = 1;
    for (int i = 0; i < N; ++i)
        l *= m_s[i];
    return l;
}

#endif

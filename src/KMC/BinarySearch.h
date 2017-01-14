// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#ifndef __kmc__binarysearch__
#define __kmc__binarysearch__

#include "BST.h"

template <class T>
class InverseMap : public BST<T,int> {
public:
	InverseMap();

	int find(T key) const;

	int operator[](T key);
};

#endif

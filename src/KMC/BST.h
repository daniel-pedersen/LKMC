// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#ifndef __kmc__bst__
#define __kmc__bst__

#include <cstddef>

template <class Key, class Value>
class BST {
public:
	BST(BST* parent = NULL);
	BST(BST* parent, Key k, Value v);
	virtual ~BST();

	virtual Value find(Key k) const;
	virtual BST* findNode(Key k) const;
	virtual void insert(Key k, Value v);
	virtual void remove(Key k);
private:
	BST* m_left;
	BST* m_right;
	BST* m_parent;
	Value m_value;
	Key m_key;
};

#endif

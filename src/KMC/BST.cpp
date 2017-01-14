// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#include "BST.h"

template <class Key, class Value>
BST<Key,Value>::BST(BST* parent) :
	m_left(NULL),
	m_right(NULL),
	m_parent(parent),
	m_value(),
	m_key()
{ }

template <class Key, class Value>
BST<Key,Value>::BST(BST* parent, Key k, Value v) :
	m_left(NULL),
	m_right(NULL),
	m_parent(parent),
	m_value(v),
	m_key(k)
{ }

template <class Key, class Value>
BST<Key,Value>::~BST()
{
	if (m_left != NULL)
		delete m_left;
	if (m_right != NULL)
		delete m_right;
}

template <class Key, class Value>
Value BST<Key,Value>::find(Key k) const
{
	if (k == m_key)
		return m_value;
	if (k < m_key) {
		if (m_left == NULL)
			return Value();
		return m_left->find(k);
	}
	if (m_right == NULL)
		return Value();
	return m_right->find(k);
}

template <class Key, class Value>
BST<Key,Value>* BST<Key,Value>::findNode(Key k) const
{
	if (k == m_key)
		return this;
	if (k < m_key) {
		if (m_left == NULL)
			return NULL;
		return m_left->findNode(k);
	}
	if (m_right == NULL)
		return NULL;
	return m_right->findNode(k);
}

template <class Key, class Value>
void BST<Key,Value>::insert(Key k, Value v)
{
	if (m_value == NULL) {
		m_value = v;
		m_key = k;
	} else if (k < m_key) {
		if (m_left == NULL) {
			m_left = new BST(this, k, v);
		} else {
			m_left->insert(k, v);
		}
	} else if (k > m_key) {
		if (m_right == NULL) {
			m_right = new BST(this, k, v);
		} else {
			m_right->insert(k, v);
		}
	} else {
		m_value = v;
	}
}

template <class Key, class Value>
void BST<Key,Value>::remove(Key k)
{
}

#pragma once

#include <cstddef>

template <typename T>
class List
{

private:
	struct Node
	{
		T _val;
		Node* _next;
		Node* _prev;

		Node(const T& val, Node* next = nullptr, Node* prew = nullptr);
	};

	Node* _head;
	Node* _tail;
	size_t _size;

public:

	List(size_t size = 0, const T& val = T());

	bool empty();
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	size_t size();
};

#pragma region CtorsAndDestructors

template<typename T>
List<T>::List(size_t size, const T& val) : _head(nullptr), _tail(nullptr), _size(size)
{
	/*Node** curNode = &_head;
	for (std::size_t i = 0; i < size; i++)
	{
		*curNode = new Node(val);
		curNode = &(*curNode)->_next;
	}*/

	if (size == 0)
		return;

	_head = new Node(val);
	_tail = _head;

	Node* curr = _head;
	for (size_t i = 1; i < size; ++i)
	{
		curr->_next = new Node(val, nullptr, curr);
		curr = curr->_next;
	}

	_tail = curr;
}

template<typename T>
List<T>::Node::Node(const T& val, Node* next, Node* prev) : _val(val), _next(next), _prev(prev) { }

#pragma endregion



template<typename T>
bool List<T>::empty()
{
	return _head == nullptr;
}

template<typename T>
T& List<T>::front()
{
	return _head->_val;
}

template<typename T>
const T& List<T>::front() const
{
	return _head->_val;
}

template<typename T>
T& List<T>::back()
{
	return _tail->_val;
}

template<typename T>
const T& List<T>::back() const
{
	return _tail->_val;
}


template<typename T>
size_t List<T>::size()
{
	return _size;
}
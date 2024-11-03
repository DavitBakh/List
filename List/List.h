#pragma once

#include <cstddef>
#include <optional>

template <typename T>
class List
{

private:
	struct Node
	{
		T _val;
		Node* _next;
		Node* _prev;

		Node(const T& val, Node* next = nullptr, Node* prev = nullptr);
	};

	Node* _head;
	Node* _tail;
	size_t _size;

public:

	List(size_t size = 0, const T& val = T());
	~List();

	bool empty();
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	size_t size();

	void push_front(const T& val);
	void push_back(const T& val);
	void pop_front();
	void pop_back();

};

#pragma region CtorsAndDestructors

template<typename T>
List<T>::List(size_t size, const T& val) : _head(new Node(T())), _tail(new Node(T())), _size(size)
{
	/*Node** curNode = &_head;
	for (std::size_t i = 0; i < size; i++)
	{
		*curNode = new Node(val);
		curNode = &(*curNode)->_next;
	}*/



	/*if (size == 0)
		return;

	_head = new Node(val);
	_tail = _head;

	Node* curr = _head;
	for (size_t i = 1; i < size; ++i)
	{
		curr->_next = new Node(val, nullptr, curr);
		curr = curr->_next;
	}

	_tail = curr;*/


	Node* temp = _head;
	for (size_t i = 0; i < size; i++)
	{
		temp->_next = new Node(val, nullptr, temp);
		temp = temp->_next;
	}

	temp->_next = _tail;
	_tail->_prev = temp;
}

template<typename T>
List<T>::~List()
{
	Node* p = _head;
	while (p != nullptr)
	{
		Node* p_next = p->_next;
		delete p;
		p = p_next;
	}
}

template<typename T>
List<T>::Node::Node(const T& val, Node* next, Node* prev) : _val(val), _next(next), _prev(prev) { }

#pragma endregion

#pragma region GetElement

template<typename T>
bool List<T>::empty()
{
	return _size == 0;
}

template<typename T>
T& List<T>::front()
{
	return _head->_next->_val;
}

template<typename T>
const T& List<T>::front() const
{
	return _head->_next->_val;
}

template<typename T>
T& List<T>::back()
{
	return _tail->_prev->_val;
}

template<typename T>
const T& List<T>::back() const
{
	return _tail->_prev->_val;
}

#pragma endregion

#pragma region Xary



template<typename T>
size_t List<T>::size()
{
	return _size;
}

template<typename T>
void List<T>::push_front(const T& val)
{
	_head->_next = new Node(val, _head->_next, _head);
	_head->_next->_next->_prev = _head->_next;

	++_size;
}

template<typename T>
void List<T>::push_back(const T& val)
{
	_tail->_prev = new Node(val, _tail, _tail->_prev);
	_tail->_prev->_prev->_next = _tail->_prev;

	++_size;
}

template<typename T>
void List<T>::pop_front()
{
	if (_head->_next == _tail)
		return;

	Node* temp = _head->_next;
	_head->_next = temp->_next;
	_head->_next->_prev = _head;

	delete temp;
	--_size;
}

template<typename T>
void List<T>::pop_back()
{
	if (_head->_next == _tail)
		return;

	Node* temp = _tail->_prev;
	_tail->_prev = temp->_prev;
	_tail->_prev->_next = _tail;

	delete temp;
	--_size;
}

#pragma endregion
#pragma once

#include <cstddef>
#include <iterator>
#include <initializer_list>

template <typename T>
class List
{

private:

#pragma region Node

	struct Node
	{
		T* _val;
		Node* _next;
		Node* _prev;

		Node(T* val = nullptr, Node* next = nullptr, Node* prev = nullptr);
		Node(const T& val, Node* next = nullptr, Node* prev = nullptr);
		~Node();
	};

	Node* _head;
	Node* _tail;
	size_t _size;

#pragma endregion

public:

#pragma region Iterator

	class iterator
	{
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::bidirectional_iterator_tag;

	private:
		Node* _current;

	public:
		iterator(Node* ptr);

		iterator& operator=(const iterator& source);
		reference operator*() const;
		pointer operator->() const;
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;

		friend class const_iterator;
		friend class List;
	};

#pragma endregion

#pragma region Reverse Iterator

	class reverse_iterator
	{
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::bidirectional_iterator_tag;

	private:
		Node* _current;

	public:
		reverse_iterator(Node* ptr);

		reverse_iterator& operator=(const reverse_iterator& source);
		reference operator*() const;
		pointer operator->() const;
		reverse_iterator& operator++();
		reverse_iterator operator++(int);
		reverse_iterator& operator--();
		reverse_iterator operator--(int);
		bool operator==(const reverse_iterator& other) const;
		bool operator!=(const reverse_iterator& other) const;

		friend class List;
	};

#pragma endregion

#pragma region Const Iterator

	class const_iterator
	{
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;
		using iterator_category = std::bidirectional_iterator_tag;

	private:
		const Node* _current;

	public:
		const_iterator(const Node* ptr);
		const_iterator(const iterator& iter);

		const_iterator& operator=(const const_iterator& source);
		reference  operator*() const;
		pointer operator->() const;
		const_iterator& operator++();
		const_iterator operator++(int);
		const_iterator& operator--();
		const_iterator operator--(int);
		bool operator==(const const_iterator& other) const;
		bool operator!=(const const_iterator& other) const;

		friend class List;
	};

#pragma endregion

#pragma region Const Reverse Iterator

	class const_reverse_iterator
	{
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;
		using iterator_category = std::bidirectional_iterator_tag;

	private:
		const Node* _current;

	public:
		const_reverse_iterator(const Node* ptr);

		const_reverse_iterator& operator=(const const_reverse_iterator& source);
		reference  operator*() const;
		pointer operator->() const;
		const_reverse_iterator& operator++();
		const_reverse_iterator operator++(int);
		const_reverse_iterator& operator--();
		const_reverse_iterator operator--(int);
		bool operator==(const const_reverse_iterator& other) const;
		bool operator!=(const const_reverse_iterator& other) const;

		friend class List;
	};

#pragma endregion

	List();
	List(size_t size);
	List(size_t size, const T& val);
	List(const List& other);
	List(std::initializer_list<T> initList);
	template <std::input_iterator iter>
	List(iter begin, iter end);
	~List();

	bool empty();
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	size_t size();
	void clear();

	void push_front(const T& val);
	void push_back(const T& val);
	void pop_front();
	void pop_back();
	void insert(const iterator& iter, const T& val);
	void erase(const iterator& iter);

	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

	List& operator=(const List& other);

	template <typename U>
	friend bool operator==(const List<U>& lhs, const List<U>& rhs);

};

#pragma region CtorsAndDestructors

template<typename T>
List<T>::List() : _head(new Node()), _tail(new Node()), _size(0)
{
	_head->_next = _tail;
	_tail->_prev = _head;
}

template<typename T>
List<T>::List(size_t size) : _head(new Node()), _tail(new Node()), _size(size)
{
	Node* temp = _head;
	for (size_t i = 0; i < size; i++)
	{
		temp->_next = new Node(T(), nullptr, temp);
		temp = temp->_next;
	}

	temp->_next = _tail;
	_tail->_prev = temp;
}

template<typename T>
List<T>::List(size_t size, const T& val) : _head(new Node()), _tail(new Node()), _size(size)
{

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
List<T>::List(const List& other) : _head(new Node()), _tail(new Node()), _size(other._size)
{
	_head->_next = _tail;
	_tail->_prev = _head;

	Node* curr = other._head->_next;
	while (curr != other._tail)
	{
		push_back(*(curr->_val));
		curr = curr->_next;
	}
}

template<typename T>
List<T>::List(std::initializer_list<T> initList) : _head(new Node()), _tail(new Node()), _size(initList.size())
{
	Node* temp = _head;
	for (auto iter = initList.begin(); iter != initList.end(); ++iter)
	{
		temp->_next = new Node(*iter, nullptr, temp);
		temp = temp->_next;
	}

	temp->_next = _tail;
	_tail->_prev = temp;
}

template<typename T>
template<std::input_iterator iter>
List<T>::List(iter begin, iter end) : _head(new Node()), _tail(new Node())
{
	Node* temp = _head;
	for (auto iter = begin; iter != end; ++iter)
	{
		temp->_next = new Node(*iter, nullptr, temp);
		temp = temp->_next;

		++_size;
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

	_size = 0;
}

template<typename T>
List<T>::Node::~Node()
{
	delete _val;
}

template<typename T>
List<T>::Node::Node(T* val, Node* next, Node* prev) : _val(val), _next(next), _prev(prev) { }

template<typename T>
List<T>::Node::Node(const T& val, Node* next, Node* prev) : _val(new T(val)), _next(next), _prev(prev) { }

template<typename T>
List<T>::iterator::iterator(Node* ptr) : _current(ptr) { }

template<typename T>
List<T>::reverse_iterator::reverse_iterator(Node* ptr) : _current(ptr) { }

template<typename T>
List<T>::const_iterator::const_iterator(const Node* ptr) : _current(ptr) { }

template<typename T>
List<T>::const_iterator::const_iterator(const iterator& iter) : _current(iter._current) { }

template<typename T>
List<T>::const_reverse_iterator::const_reverse_iterator(const Node* ptr) : _current(ptr) { }

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
	return *(_head->_next->_val);
}

template<typename T>
const T& List<T>::front() const
{
	return *(_head->_next->_val);
}

template<typename T>
T& List<T>::back()
{
	return *(_tail->_prev->_val);
}

template<typename T>
const T& List<T>::back() const
{
	return *(_tail->_prev->_val);
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

template<typename T>
void List<T>::clear()
{
	Node* p = _head->_next;
	while (p != _tail)
	{
		Node* p_next = p->_next;
		delete p;
		p = p_next;
	}

	_head->_next = _tail;
	_tail->_prev = _head;

	_size = 0;
}

template<typename T>
void List<T>::insert(const List<T>::iterator& iter, const T& val)
{

	Node* newNode = new Node(val, iter._current, iter._current->_prev);

	iter._current->_prev->_next = newNode;
	iter._current->_prev = newNode;

	++_size;
}

template<typename T>
void List<T>::erase(const iterator& iter)
{

	iter._current->_prev->_next = iter._current->_next;
	iter._current->_next->_prev = iter._current->_prev;

	delete iter._current;
	--_size;
}

#pragma endregion

#pragma region Operators

template<typename T>
bool operator==(const List<T>& lhs, const List<T>& rhs)
{
	typename List<T>::Node* lhsP = lhs._head->_next;
	typename List<T>::Node* rhsP = rhs._head->_next;

	while (lhsP != nullptr && rhsP != nullptr)
	{
		if (lhsP->_val && rhsP->_val && *(lhsP->_val) != *(rhsP->_val))
			return false;

		lhsP = lhsP->_next;
		rhsP = rhsP->_next;
	}

	return lhsP == rhsP;
}

template<typename T>
bool operator!=(const List<T>& lhs, const List<T>& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
List<T>& List<T>::operator=(const List& other)
{
	if (this == &other) return *this;

	clear();

	Node* curr = other._head->_next;
	while (curr != other._tail)
	{
		push_back(*(curr->_val));
		curr = curr->_next;
	}

	return *this;
}

#pragma endregion

#pragma region Iterator

template<typename T>
List<T>::iterator List<T>::begin()
{
	return iterator(_head->_next);
}

template<typename T>
List<T>::iterator List<T>::end()
{
	return iterator(_tail);
}

template<typename T>
List<T>::iterator::reference List<T>::iterator::operator*() const
{
	return *(_current->_val);
}

template<typename T>
List<T>::iterator::pointer List<T>::iterator::operator->() const
{
	return _current->_val;
}

template<typename T>
List<T>::iterator& List<T>::iterator::operator++()
{
	_current = _current->_next;
	return *this;
}

template<typename T>
List<T>::iterator List<T>::iterator::operator++(int)
{
	iterator result(*this);
	++(*this);
	return result;
}

template<typename T>
List<T>::iterator& List<T>::iterator::operator--()
{
	_current = _current->_prev;
	return *this;
}

template<typename T>
List<T>::iterator List<T>::iterator::operator--(int)
{
	iterator result(*this);
	--(*this);
	return result;
}


template<typename T>
bool List<T>::iterator::operator==(const List<T>::iterator& other) const
{
	return this->_current == other._current;
}

template<typename T>
bool List<T>::iterator::operator!=(const List<T>::iterator& other) const
{
	return this->_current != other._current;
}

template<typename T>
List<T>::iterator& List<T>::iterator::operator=(const iterator& source)
{
	this->_current = source._current;
	return *this;
}

#pragma endregion

#pragma region Reverse Iterator

template<typename T>
List<T>::reverse_iterator List<T>::rbegin()
{
	return reverse_iterator(_tail->_prev);
}

template<typename T>
List<T>::reverse_iterator List<T>::rend()
{
	return reverse_iterator(_head);
}

template<typename T>
List<T>::reverse_iterator::reference List<T>::reverse_iterator::operator*() const
{
	return *(_current->_val);
}

template<typename T>
List<T>::reverse_iterator::pointer List<T>::reverse_iterator::operator->() const
{
	return _current->_val;
}

template<typename T>
List<T>::reverse_iterator& List<T>::reverse_iterator::operator++()
{
	_current = _current->_prev;
	return *this;
}

template<typename T>
List<T>::reverse_iterator List<T>::reverse_iterator::operator++(int)
{
	reverse_iterator result(*this);
	++(*this);
	return result;
}

template<typename T>
List<T>::reverse_iterator& List<T>::reverse_iterator::operator--()
{
	_current = _current->_next;
	return *this;
}

template<typename T>
List<T>::reverse_iterator List<T>::reverse_iterator::operator--(int)
{
	reverse_iterator result(*this);
	--(*this);
	return result;
}

template<typename T>
bool List<T>::reverse_iterator::operator==(const List<T>::reverse_iterator& other) const
{
	return this->_current == other._current;
}

template<typename T>
bool List<T>::reverse_iterator::operator!=(const List<T>::reverse_iterator& other) const
{
	return this->_current != other._current;
}

template<typename T>
List<T>::reverse_iterator& List<T>::reverse_iterator::operator=(const reverse_iterator& source)
{
	this->_current = source._current;
	return *this;
}


#pragma endregion

#pragma region Const Iterator

template<typename T>
List<T>::const_iterator List<T>::begin() const
{
	return const_iterator(_head->_next);
}

template<typename T>
List<T>::const_iterator List<T>::end() const
{
	return const_iterator(_tail);
}

template<typename T>
List<T>::const_iterator List<T>::cbegin() const
{
	return const_iterator(_head->_next);
}

template<typename T>
List<T>::const_iterator List<T>::cend() const
{
	return const_iterator(_tail);
}

template<typename T>
List<T>::const_iterator::reference List<T>::const_iterator::operator*() const
{
	return *(_current->_val);
}

template<typename T>
List<T>::const_iterator::pointer List<T>::const_iterator::operator->() const
{
	return _current->_val;
}

template<typename T>
List<T>::const_iterator& List<T>::const_iterator::operator++()
{
	_current = _current->_next;
	return *this;
}

template<typename T>
List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
	const_iterator result(*this);
	++(*this);
	return result;
}

template<typename T>
List<T>::const_iterator& List<T>::const_iterator::operator--()
{
	_current = _current->_prev;
	return *this;
}

template<typename T>
List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
	const_iterator result(*this);
	--(*this);
	return result;
}

template<typename T>
bool List<T>::const_iterator::operator==(const List<T>::const_iterator& other) const
{
	return this->_current == other._current;
}

template<typename T>
bool List<T>::const_iterator::operator!=(const List<T>::const_iterator& other) const
{
	return this->_current != other._current;
}

template<typename T>
List<T>::const_iterator& List<T>::const_iterator::operator=(const const_iterator& source)
{
	this->_current = source._current;
	return *this;
}

#pragma endregion

#pragma region Const Reverse Iterator

template<typename T>
List<T>::const_reverse_iterator List<T>::rbegin() const
{
	return const_reverse_iterator(_tail->_prev);
}

template<typename T>
List<T>::const_reverse_iterator List<T>::rend() const
{
	return const_reverse_iterator(_head);
}

template<typename T>
List<T>::const_reverse_iterator List<T>::crbegin() const
{
	return const_reverse_iterator(_tail->_prev);
}

template<typename T>
List<T>::const_reverse_iterator List<T>::crend() const
{
	return const_reverse_iterator(_head);
}

template<typename T>
List<T>::const_reverse_iterator::reference List<T>::const_reverse_iterator::operator*() const
{
	return *(_current->_val);
}

template<typename T>
List<T>::const_reverse_iterator::pointer List<T>::const_reverse_iterator::operator->() const
{
	return _current->_val;
}

template<typename T>
List<T>::const_reverse_iterator& List<T>::const_reverse_iterator::operator++()
{
	_current = _current->_prev;
	return *this;
}

template<typename T>
List<T>::const_reverse_iterator List<T>::const_reverse_iterator::operator++(int)
{
	const_reverse_iterator result(*this);
	++(*this);
	return result;
}

template<typename T>
List<T>::const_reverse_iterator& List<T>::const_reverse_iterator::operator--()
{
	_current = _current->_next;
	return *this;
}

template<typename T>
List<T>::const_reverse_iterator List<T>::const_reverse_iterator::operator--(int)
{
	const_reverse_iterator result(*this);
	--(*this);
	return result;
}

template<typename T>
bool List<T>::const_reverse_iterator::operator==(const List<T>::const_reverse_iterator& other) const
{
	return this->_current == other._current;
}

template<typename T>
bool List<T>::const_reverse_iterator::operator!=(const List<T>::const_reverse_iterator& other) const
{
	return this->_current != other._current;
}

template<typename T>
List<T>::const_reverse_iterator& List<T>::const_reverse_iterator::operator=(const const_reverse_iterator& source)
{
	this->_current = source._current;
	return *this;
}


#pragma endregion




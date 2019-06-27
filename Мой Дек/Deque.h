#pragma once
#include <iostream>
#include <algorithm>
template<class T>
class Deque
{
private:
	
	int size;
	//Класс Node - вложенный, он доступен только классу Deque, так как описан
	//в его private секции, при этом все поля и методы Node находятся в public, 
	//чтобы не было проблем с доступом в самом Deque
	template<class T>
	class Node
	{
	public:
		T data;
		Node *pNext, *pPrev;
		Node(T data = T(), Node* prev = nullptr, Node* next = nullptr)
		{
			this->data = data;
			this->pPrev = prev;
			this->pNext = next;
		}
	};
	
	
public:

	Node<T> *head, *tail;
	Deque();
	Deque(const Deque&);

	void push_back(const T&);
	void push_front(const T&);

	const T pop_back();
	const T pop_front();

	const T get_head() const;
	const T get_tail() const;
	void clear();
	const Deque& operator = (const Deque&);

	void Print_All();
	void RPrint_All();

	bool empty() const;
	const Deque& sort();
	virtual ~Deque();

	const int GetSize();

	template <class T>
	friend std::ostream& operator << (std::ostream& stream, const Deque<T>&);
};




template<class T>
inline Deque<T>::Deque()
{
	size = 0;
	head = nullptr;
	tail = nullptr;
}

template<class T>
inline Deque<T>::Deque(const Deque& sourse)
{
	Node<T> *i = sourse.head;
	while (i !=  nullptr)
	{
		push_back(i->data);
		i = i->pNext;
	}

}



template<class T>
inline void Deque<T>::push_back(const T& data)
{
	Node<T> *current = new Node<T>(data);
	if (!size)
		head = current;
	else
	{
		tail->pNext = current;
		current->pPrev = tail;
	}
	tail = current;
	
	size++;
}

template<class T>
inline void Deque<T>::push_front(const T& data)
{
	Node<T> *current = new Node<T>(data);
	if (!size)
		tail = current;
	else
	{
		head->pPrev = current;
		current->pNext = head;
	}
	head = current;
	
	size++;
}

template<class T>
inline const T Deque<T>::pop_back()
{
	if (!size)
		return T();
	
	T current = tail->data;
	Node<T> *newtail;
	if (tail == head)
	{
		newtail = nullptr;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		newtail = tail->pPrev;
		delete tail;
		tail = newtail;
		tail->pNext = nullptr;
	}
	
	size--;
	return current;
}

template<class T>
inline const T Deque<T>::pop_front()
{
	if (!size)
		return T();
	T current = head->data;
	Node<T> *newhead;
	if (tail == head)
	{
		newhead = nullptr;
		tail = nullptr;
		head = nullptr;
	}
	else
	{
		newhead = head->pNext;
		delete head;
		head = newhead;
		head->pPrev = nullptr;
	}

	size--;
	return current;

}

template<class T>
inline const T Deque<T>::get_head() const
{
	return this->head->data;
}

template<class T>
inline const T Deque<T>::get_tail() const
{
	return this->tail->data;
}

template<class T>
inline void Deque<T>::clear()
{
	while (size)
		this->pop_back();
}

template<class T>
inline const Deque<T>& Deque<T>::operator=(const Deque& sourse)
{
	if (this != &sourse)
	{
		this->clear();
		Node<T> *i = sourse.head;
		while (i != nullptr)
		{
			push_back(i->data);
			i = i->pNext;
		}
	}
	return *this;
}

template<class T>
inline void Deque<T>::Print_All()
{
	Node<T>* i = this->head;
	while (i != nullptr)
	{
		std::cout << i->data << " ";
		i = i->pNext;
	}
	std::cout << std::endl;
}

template<class T>
inline void Deque<T>::RPrint_All()
{
	Node<T>* i = this->tail;
	while (i != nullptr)
	{
		std::cout << i->data << " ";
		i = i->pPrev;
	}
	std::cout << std::endl;
}



template<class T>
inline bool Deque<T>::empty() const
{
	return this->size == 0;
}

//////////////////////////
//Сортировка
inline int comp(const void* x1, const void* x2)
{
	return strcmp(*(const char **)x1, *(const char**)x2);
}

template<>
inline const Deque<const char*> & Deque<const char*>::sort()
{
	const int n = this->size;
	const char **arr = new const char*[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = this->pop_back();
	}
	
	qsort(arr, n, sizeof(char**), comp);
	for (int i = 0; i < n; i++)
	{
		this->push_back(arr[i]);
	}
	return *this;
}

template<class T>
inline const Deque<T> & Deque<T>::sort()
{
	const int n = this->size;
	T *arr = new T[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = this->pop_back();
	}
	std::sort(arr, arr + n);
	for (int i = 0; i < n; i++)
	{
		this->push_back(arr[i]);
	}
	return *this;
}

template<class T>
inline Deque<T>::~Deque()
{
	this->clear();
}

template<class T>
inline const int Deque<T>::GetSize()
{
	return size;
}

template<class T>
std::ostream & operator<<(std::ostream & stream, const Deque<T>& sourse)
{
	auto *i = sourse.head;
	while (i != nullptr)
	{
		stream << i->data << " ";
		i = i->pNext;
	}
	return stream;
}

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

// Copyright 2002-2009, Daniel Fontijne, University of Amsterdam -- fontijne@science.uva.nl

#ifndef _LIST_STACK_H_
#define _LIST_STACK_H_

// trivial stack template
template <class type> class tsStack {
public:
	tsStack();
	~tsStack();

	void initToNothing();

	type top() const;
	type pop();
	void push(type item);
	void clear();
	
protected:
	type *m_stack;
	int m_top;
};

// trivial list of tsXXXData
template <class type> class tsItemList {
public:
	tsItemList();
	~tsItemList();

	void initToNothing();

	int clear(); // removes all from list
	int add(const type *item);
	int set(int idx, const type item);
	int set(int idx, const type *item);

	inline type&operator[](int idx) {return m_item[idx];};

	int m_nb;
	type *m_item;

protected:
	int m_max; // allocated length of m_item (>= m_nb)
	int ensureMax(int nb);
};

template <class type>tsStack<type>::tsStack() {
	initToNothing();
	m_top = -1;
}

template <class type>tsStack<type>::~tsStack() {
	clear();
	initToNothing();
}

template <class type>void tsStack<type>::initToNothing() {
	m_stack = NULL;
	m_top = -1;
}

template <class type>type tsStack<type>::top() const {
	if (m_top < 0) return -1;
	else return m_stack[m_top];
}

template <class type>void tsStack<type>::push(type item) {
	m_top++;
	m_stack = (type*)realloc(m_stack, sizeof(type) * (m_top + 1));
	m_stack[m_top] = item;
}

template <class type>void tsStack<type>::clear() {
	if (m_stack) free(m_stack);
	m_stack = NULL;
	m_top = -1;
}

template <class type>type tsStack<type>::pop() {
	if (m_top < 0) return (type)-1;
	else return m_stack[m_top--];	
}

template <class type>tsItemList<type>::tsItemList() {
	initToNothing();
}

template <class type>tsItemList<type>::~tsItemList() {
	clear();
	initToNothing();
}

template <class type>void tsItemList<type>::initToNothing() {
	m_item = NULL;
	m_nb = m_max = 0;
}

template <class type>int tsItemList<type>::clear() {
	if (m_item) free(m_item);
	initToNothing();
	return 0;
}

template <class type>int tsItemList<type>::add(const type *item) {
	int err;
	if (err = ensureMax(m_nb + 1)) return err;
	memcpy(m_item + m_nb, item, sizeof(type));
	m_nb++;
	return 0;
}

template <class type>int tsItemList<type>::set(int idx, const type item) {
	if (idx >= m_nb) return -1;
	memcpy(m_item + idx, &item, sizeof(type));
	return 0;
}

template <class type>int tsItemList<type>::set(int idx, const type *item) {
	if (idx >= m_nb) return -1;
	memcpy(m_item + idx, item, sizeof(type));
	return 0;
}

template <class type>int tsItemList<type>::ensureMax(int nb) {
	if (nb < 0) return -1;
	if (nb <= m_max) return 0;

	m_max = (m_max) ? m_max * 2 : 2;
	if ( (m_item = (type*)realloc(m_item, m_max * sizeof(type))) == NULL) {
		printf("tsItemList::ensureMax(): memory allocation failure for '%d' bytes\n", sizeof(type));
		return -1;
	}

	memset(m_item + m_nb, 0, sizeof(type) * (m_max - m_nb));

	return 0;
}

#endif /* _LIST_STACK_H_ */

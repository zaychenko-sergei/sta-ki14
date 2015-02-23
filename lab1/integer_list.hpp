#ifndef _INTEGER_LIST_HPP_
#define _INTEGER_LIST_HPP_

#include <iostream>


struct IntegerList
{
    struct Node
    {
        int m_value;
        Node * m_pNext;
    };

    Node * m_pFirst, * m_pLast;
};


void IntegerListInit ( IntegerList & _list );

void IntegerListDestroy ( IntegerList & _list );

bool IntegerListIsEmpty ( const IntegerList & _list );

int IntegerListSize ( const IntegerList & _list );

void IntegerListClear ( IntegerList & _list );

void IntegerListPushBack ( IntegerList & _list, int _data );

void IntegerListPushFront ( IntegerList & _list, int _data );

void IntegerListInsertAfter ( IntegerList & _list, IntegerList::Node * _pPrevNode, int _data );

void IntegerListInsertBefore ( IntegerList & _list, IntegerList::Node * _pNextNode, int _data );

void IntegerListPopBack ( IntegerList & _list );

void IntegerListPopFront ( IntegerList & _list );

void IntegerListDeleteAfter ( IntegerList & _list, IntegerList::Node * _pPrevNode );

void IntegerListDeleteBefore ( IntegerList & _list, IntegerList::Node * _pNextNode );

void IntegerListDeleteNode ( IntegerList & _list, IntegerList::Node * _pNode );

void IntegerListRead ( IntegerList & _list, std::istream & _i );

void IntegerListReadTillZero ( IntegerList & _list, std::istream & _i );

void IntegerListPrint ( const IntegerList & _list, std::ostream & _o, char _sep = ' ' );



#endif //  _INTEGER_FORWARD_LIST_HPP_
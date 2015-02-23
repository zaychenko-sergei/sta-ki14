#include "integer_list.hpp"
#include <cassert>

void IntegerListInit ( IntegerList & _list )
{
    _list.m_pFirst = _list.m_pLast = nullptr;
}


void IntegerListDestroy ( IntegerList & _list )
{
    IntegerListClear( _list );
}


void IntegerListClear ( IntegerList & _list )
{
    IntegerList::Node * pCurrent = _list.m_pFirst;
    while ( pCurrent )
    {
        IntegerList::Node * pTemp = pCurrent->m_pNext;
        delete pCurrent;
        pCurrent = pTemp;
    }

    _list.m_pFirst = _list.m_pLast = nullptr;
}


bool IntegerListIsEmpty ( const IntegerList & _list )
{
    return _list.m_pFirst == nullptr;
}


int IntegerListSize ( const IntegerList & _list )
{
    int nElements = 0;
    const IntegerList::Node * pNode = _list.m_pFirst;
    while ( pNode )
    {
        ++ nElements;
        pNode = pNode->m_pNext;
    }

    return nElements;
}


void IntegerListPushBack ( IntegerList & _list, int _data )
{
    IntegerList::Node * pNewNode = new IntegerList::Node;
    pNewNode->m_value = _data;
    pNewNode->m_pNext = nullptr;

    if ( ! _list.m_pFirst )
    {
        assert( ! _list.m_pLast );
        _list.m_pFirst = pNewNode;
    }
    else
        _list.m_pLast->m_pNext = pNewNode;

    _list.m_pLast = pNewNode;
}


void IntegerListPushFront ( IntegerList & _list, int _data )
{
    IntegerList::Node * pNewNode = new IntegerList::Node;
    pNewNode->m_value = _data;
    pNewNode->m_pNext = _list.m_pFirst;

    _list.m_pFirst = pNewNode;
    
    if ( ! _list.m_pLast )
        _list.m_pLast = pNewNode;
}


void IntegerListInsertAfter ( IntegerList & _list, IntegerList::Node * _pPrevNode, int _data )
{
    assert( ! IntegerListIsEmpty( _list ) );

    if ( _pPrevNode == _list.m_pLast )
        IntegerListPushBack( _list, _data );

    else
    {
        IntegerList::Node * pNewNode = new IntegerList::Node;
        pNewNode->m_value = _data;

        pNewNode->m_pNext = _pPrevNode->m_pNext;

        _pPrevNode->m_pNext = pNewNode;
    }
}


void IntegerListInsertBefore ( IntegerList & _list, IntegerList::Node * _pNextNode, int _data )
{
    assert( ! IntegerListIsEmpty( _list ) );

    if ( _pNextNode == _list.m_pFirst )
        IntegerListPushFront( _list, _data );

    else
    {
        IntegerList::Node * pCurrent = _list.m_pFirst;
        while ( pCurrent && pCurrent->m_pNext != _pNextNode )
            pCurrent = pCurrent->m_pNext;

        assert( pCurrent );

        IntegerList::Node * pNewNode = new IntegerList::Node;
        pNewNode->m_value = _data;

        pNewNode->m_pNext = _pNextNode;
        
        pCurrent->m_pNext = pNewNode;

    }
}


void IntegerListPopFront ( IntegerList & _list )
{
    assert( ! IntegerListIsEmpty( _list ) );

    IntegerList::Node * pFirst = _list.m_pFirst;

    if ( _list.m_pFirst == _list.m_pLast )
        _list.m_pFirst = _list.m_pLast = nullptr;

    else
        _list.m_pFirst = pFirst->m_pNext;

    delete pFirst;    
}


void IntegerListPopBack ( IntegerList & _list )
{
    assert( ! IntegerListIsEmpty( _list ) );

    IntegerList::Node * pLast = _list.m_pLast;

    if ( _list.m_pFirst == _list.m_pLast )
        _list.m_pFirst = _list.m_pLast = nullptr;

    else
    {
        IntegerList::Node * pCurrent = _list.m_pFirst;
        while ( pCurrent->m_pNext != _list.m_pLast )
            pCurrent = pCurrent->m_pNext;

        _list.m_pLast = pCurrent;
        pCurrent->m_pNext = nullptr;
    }

    delete pLast;
}


void IntegerListDeleteAfter ( IntegerList & _list, IntegerList::Node * _pPrevNode )
{
    assert( ! IntegerListIsEmpty( _list ) );

    assert( _list.m_pLast != _pPrevNode );

    IntegerList::Node * pDyingNode = _pPrevNode->m_pNext;
    _pPrevNode->m_pNext = pDyingNode->m_pNext;

    if ( _list.m_pLast == pDyingNode )
        _list.m_pLast = _pPrevNode;
        
    delete pDyingNode;
}


void IntegerListDeleteBefore ( IntegerList & _list, IntegerList::Node * _pNextNode )
{
    assert( ! IntegerListIsEmpty( _list ) );

    assert( _list.m_pFirst != _pNextNode );

    IntegerList::Node * pPrevNode = _list.m_pFirst, * pCurrentNode = _list.m_pFirst->m_pNext;
    if ( pCurrentNode == _pNextNode )
    {
        delete _list.m_pFirst;
        _list.m_pFirst = _pNextNode;
    }

    else
    {
        while ( pCurrentNode->m_pNext != _pNextNode )
        {
            pPrevNode = pCurrentNode;
            pCurrentNode = pCurrentNode->m_pNext;
        }

        pPrevNode->m_pNext = _pNextNode;
        delete pCurrentNode;
    }
}


void IntegerListDeleteNode ( IntegerList & _list, IntegerList::Node * _pNode )
{
    if ( _list.m_pFirst == _pNode )
        IntegerListPopFront( _list );

    else if ( _list.m_pLast == _pNode )
        IntegerListPopBack( _list );

    else
        IntegerListDeleteBefore( _list, _pNode->m_pNext );
}


void IntegerListPrint ( const IntegerList & _list, std::ostream & _stream, char _sep )
{
    const IntegerList::Node * pCurrent = _list.m_pFirst;
    while ( pCurrent )
    {
        _stream << pCurrent->m_value << _sep;
        pCurrent = pCurrent->m_pNext;
    }
}


void IntegerListRead ( IntegerList & _list, std::istream & _stream )
{
    while ( true )
    {
        int temp;
        _stream >> temp;
        if ( _stream )
            IntegerListPushBack( _list, temp );
        else
            break;
    }    
}


void IntegerListReadTillZero ( IntegerList & _list, std::istream & _stream )
{
    while ( true )
    {
        int temp;
        _stream >> temp;
        if ( _stream && temp != 0 )
            IntegerListPushBack( _list, temp );
        else
            break;
    }
}
#include "integer_set.hpp"
#include "integer_list.hpp"

#include <cassert>


struct IntegerSet
{
    IntegerList m_data;
};


IntegerSet * IntegerSetCreate ()
{
    IntegerSet * pSet = new IntegerSet;
    IntegerListInit( pSet->m_data );
    return pSet;
}


void IntegerSetDestroy ( IntegerSet * _pSet )
{
    IntegerListDestroy( _pSet->m_data );
    delete _pSet;
}


void IntegerSetClear ( IntegerSet & _set )
{
    IntegerListClear( _set.m_data );
}


bool IntegerSetIsEmpty ( const IntegerSet & _set )
{
    return IntegerListIsEmpty( _set.m_data );
}


int IntegerSetSize ( const IntegerSet & _set )
{
    return IntegerListSize( _set.m_data );
}


bool IntegerSetHasKey ( const IntegerSet & _set, int _key )
{
    IntegerList::Node * pNode = _set.m_data.m_pFirst;
    while ( pNode )
    {
        if ( pNode->m_value == _key )
            return true;
        else if ( pNode->m_value > _key )
            return false;
        pNode = pNode->m_pNext;
    }
    return false;
}


void IntegerSetInsertKey ( IntegerSet & _set, int _key )
{
    if ( IntegerListIsEmpty( _set.m_data ) )
        IntegerListPushBack( _set.m_data, _key );

    else
    {
        IntegerList::Node * pNode = _set.m_data.m_pFirst;
        if ( _key < pNode->m_value )
            IntegerListPushFront( _set.m_data, _key );

        else
        {
            IntegerList::Node * pPrevNode = nullptr;
            while ( pNode )
            {
                if ( pNode->m_value == _key )
                    return;

                else if ( ! pNode->m_pNext  )
                {
                    IntegerListPushBack( _set.m_data, _key );
                    return;
                }

                else if ( pNode->m_pNext->m_value > _key )
                {
                    IntegerListInsertAfter( _set.m_data, pNode, _key );
                    return;
                }

                else
                    pNode = pNode->m_pNext;
            }

            assert( ! "We should never get here" );
        }
    }
}


void IntegerSetDeleteKey ( IntegerSet & _set, int _key )
{
    IntegerList::Node * pNode = _set.m_data.m_pFirst;
    while ( pNode )
    {
        if ( pNode->m_value == _key )
        {
            IntegerListDeleteNode( _set.m_data, pNode );
            return;
        }
        else if ( pNode->m_value > _key )
            break;

        pNode = pNode->m_pNext;
    }

    assert( !"Key is unavailble!" );
}


void IntegerSetInsertAllKeys ( const IntegerSet & _sourceSet, IntegerSet & _targetSet )
{
    IntegerList::Node * pNode = _sourceSet.m_data.m_pFirst;
    while ( pNode )
    {
        IntegerSetInsertKey( _targetSet, pNode->m_value );
        pNode = pNode->m_pNext;
    }
}


void IntegerSetUnite ( const IntegerSet & _set1,
                       const IntegerSet & _set2,
                       IntegerSet & _targetSet )
{
    IntegerSetClear( _targetSet );

    IntegerList::Node * pNode1 = _set1.m_data.m_pFirst;
    IntegerList::Node * pNode2 = _set2.m_data.m_pFirst;
    while ( pNode1 || pNode2 )
    {
        if ( pNode1 && pNode2 )
        {
            if ( pNode1->m_value < pNode2->m_value )
            {
                IntegerListPushBack( _targetSet.m_data, pNode1->m_value );
                pNode1 = pNode1->m_pNext;
            }
            else if ( pNode1->m_value > pNode2->m_value )
            {
                IntegerListPushBack( _targetSet.m_data, pNode2->m_value );
                pNode2 = pNode2->m_pNext;
            }
            else
            {
                IntegerListPushBack( _targetSet.m_data, pNode1->m_value );
                pNode1 = pNode1->m_pNext;
                pNode2 = pNode2->m_pNext;
            }
        }
        else if ( pNode1 )
        {
            IntegerListPushBack( _targetSet.m_data, pNode1->m_value );
            pNode1 = pNode1->m_pNext;
        }
        else
        {
            IntegerListPushBack( _targetSet.m_data, pNode2->m_value );
            pNode2 = pNode2->m_pNext;
        }
    }
}


void IntegerSetIntersect ( const IntegerSet & _set1,
                           const IntegerSet & _set2,
                           IntegerSet & _targetSet )
{
    IntegerSetClear( _targetSet );

    IntegerList::Node * pNode1 = _set1.m_data.m_pFirst;
    IntegerList::Node * pNode2 = _set2.m_data.m_pFirst;
    while ( pNode1 && pNode2 )
    {
        if ( pNode1->m_value == pNode2->m_value )
            IntegerListPushBack( _targetSet.m_data, pNode1->m_value );

        else if ( pNode1->m_value < pNode2->m_value )
            pNode1 = pNode1->m_pNext;

        else
            pNode2 = pNode2->m_pNext;
    }
}


void IntegerSetDifference ( const IntegerSet & _set1,
                            const IntegerSet & _set2,
                            IntegerSet & _targetSet )
{
    IntegerSetClear( _targetSet );

    IntegerList::Node * pNode1 = _set1.m_data.m_pFirst;
    IntegerList::Node * pNode2 = _set1.m_data.m_pFirst;
    while ( pNode1 )
    {
        if ( pNode2 )
        {
            if ( pNode1->m_value == pNode2->m_value )
            {
                pNode1 = pNode1->m_pNext;
                pNode2 = pNode2->m_pNext;
            }
            else if ( pNode1->m_value < pNode2->m_value )
            {
                IntegerListPushBack( _targetSet.m_data, pNode1->m_value );
                pNode1 = pNode1->m_pNext;
            }
            else
                pNode2 = pNode2->m_pNext;
        }
        else
        {
            IntegerListPushBack( _targetSet.m_data, pNode1->m_value );
            pNode1 = pNode1->m_pNext;
        }
    }
}


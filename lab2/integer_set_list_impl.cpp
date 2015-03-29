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


bool IntegerSetHasKey ( const IntegerSet & _set, int _key )
{
    IntegerList::Node * pNode = _set.m_data.m_pFirst;
    while ( pNode )
    {
        if ( pNode->m_value == _key )
            return true;
        pNode = pNode->m_pNext;
    }
    return false;
}


void IntegerSetInsertKey ( IntegerSet & _set, int _key )
{
    if ( ! IntegerSetHasKey( _set, _key ) )
        IntegerListPushBack( _set.m_data, _key );
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

    IntegerSetInsertAllKeys( _set1, _targetSet );
    IntegerSetInsertAllKeys( _set2, _targetSet );
}


void IntegerSetIntersect ( const IntegerSet & _set1,
                           const IntegerSet & _set2,
                           IntegerSet & _targetSet )
{
    IntegerSetClear( _targetSet );

    IntegerList::Node * pNode = _set1.m_data.m_pFirst;
    while ( pNode )
    {
        if ( IntegerSetHasKey( _set2, pNode->m_value ) )
            IntegerSetInsertKey( _targetSet, pNode->m_value );
        pNode = pNode->m_pNext;
    }
}


void IntegerSetDifference( const IntegerSet & _set1,
                           const IntegerSet & _set2,
                           IntegerSet & _targetSet )
{
    IntegerSetClear( _targetSet );

    IntegerList::Node * pNode = _set1.m_data.m_pFirst;
    while ( pNode )
    {
        if ( ! IntegerSetHasKey( _set2, pNode->m_value ) )
            IntegerSetInsertKey( _targetSet, pNode->m_value );
        pNode = pNode->m_pNext;
    }
}